-module (lexer).
-export ([main/1]).

-mode(compile).

-define (is_digit(L), (is_number(L) and (L >= 48) and (L =< 57))).
-define (is_letter(L), (is_number(L) and (((L >= 65) and (L =< 90)) or ((L >= 97) and (L =< 120))))).
-define (is_small_letter(L), (is_number(L) and ((L >= 97) and (L =< 120)))).
-define (is_space(L), (is_number(L) and (L =:= 32) or (L =:= 9))).

main([File]) ->
    case file:open(File, [read]) of
    	{ok, Fd} ->
    		tables:init(),
    		State = dict:from_list([{lastId, -1}, {line_num, 1}, {symbol_num, 1}]),
    		read_file(Fd, State, []),
    		halt();
    	{error, _Reason} ->
    		io:format("Can not open the file", []),
    		halt(1)
   	end;
main(_) ->
	io:format("usage: lexer FILE~n", []),
    halt().

read_file(Fd, State, Prog) ->	
	case file:read_line(Fd) of
		{ok, D} ->
			Data = string:strip(D, right, $\n),				
			{ok, NState1, NProg} = loop(Data, State, Prog),
			NState2 = dict:update_counter(line_num, 1, dict:store(symbol_num, 1, NState1)),	
			read_file(Fd, NState2, NProg);
		eof ->
			io:format("LEX:~n ~p~n", [lists:reverse(Prog)]),
			ok
	end.

loop([H|T], State, Prog) when ?is_digit(H) ->
	{L, Const, Len} = get_const(T, list_to_integer([H])),
	loop(L, inc_sym_count(State, Len), [{const, Const}|Prog]);

loop([H|T], State, Prog) when ?is_letter(H) ->
	{L, Str, Len} = get_str(T, H),
	case tables:find_sym(Str) of
		error ->
			case check_ident(Str) of
				ok ->
					{ok, LastId} = dict:find(lastId, State),
					[{current, Id}, {lastId, NewLastId}] = tables:add_id(Str, LastId),
					NState = dict:store(lastId, NewLastId, State),
					loop(L, inc_sym_count(NState, Len), [{id, Id}|Prog]);
				error ->
					{ok, Line} = dict:find(line_num, State),
					{ok, Sym} = dict:find(symbol_num, State),
					io:format("line ~p, symbol ~p - Error: unknown symbol ~n", [Line, Sym]),
					loop(T, inc_sym_count(State, Len), Prog)
			end;
		Res ->
			loop(L, inc_sym_count(State, Len), [Res|Prog])
	end;

loop([H|T], State, Prog) when ?is_space(H) ->
	loop(T, inc_sym_count(State), Prog);

loop([H|T], State, Prog) ->
	case tables:find_sym([H]) of
		{Class, Id} = Res -> 
			loop(T, inc_sym_count(State), [Res|Prog]);
		error ->  
			{ok, Line} = dict:find(line_num, State),
			{ok, Sym} = dict:find(symbol_num, State),
			io:format("line ~p, symbol ~p - Error: unknown symbol ~n", [Line, Sym]),
			loop(T, inc_sym_count(State), Prog)
	end;

loop([], State, Prog)->
	{ok, State, Prog}.

% Инкремент счетчика символов в состоянии
inc_sym_count(State) ->
	inc_sym_count(State, 1).
inc_sym_count(State, Inc) ->
	dict:update_counter(symbol_num, Inc, State).

% Получение константы
get_const(L, C) ->
	get_const(L, C, 1).
get_const([H|T], Const, Len) when ?is_digit(H) ->
	Int = list_to_integer([H]),
	get_const(T, Const*10 + Int, Len + 1);
get_const(L, Const, Len) ->
	{L, Const, Len}.

% Получение строки для идентификатора или ключевого слова
get_str(L, I) ->
	get_str(L, [I], 1).
get_str([H|T], Ident, Len) when ?is_letter(H) ->
	get_str(T, [H|Ident], Len + 1);
get_str(L, Ident, Len) ->
	{L, lists:reverse(Ident), Len}.

% Проверка, чтобы идентификатор не содержал заглавных букв
check_ident([H|T]) when ?is_small_letter(H) ->
	check_ident(T);
check_ident([]) ->
	ok;
check_ident(_) ->
	error.