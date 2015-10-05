-module (lexer).
-export ([main/1]).

-mode(compile).

-define (is_digit(L), (is_number(L) and (L >= 48) and (L =< 57))).
-define (is_letter(L), (is_number(L) and (((L >= 65) and (L =< 90)) or ((L >= 97) and (L =< 120))))).
-define (is_space(L), (is_number(L) and (L =:= 32) or (L =:= 9))).

main([File]) ->
    io:format("File ~p~n", [File]),
    case file:open(File, [read]) of
    	{ok, Fd} ->
    		tables:init(),
    		file_read(Fd),
    		halt();
    	{error, _Reason} ->
    		io:format("Can not open the file", []),
    		halt(1)
   	end;
main(_) ->
	io:format("Holy moly it's simple.~n", []),
    halt().

file_read(Fd) ->
	case file:read_line(Fd) of
		{ok, D} ->
			Data = string:strip(D, right, $\n),
			io:format("~w~n", [Data]),
			loop(Data),
			file_read(Fd);
		eof ->
			ok
	end.

loop([H|T]) when ?is_digit(H) ->
	{L, Const} = get_const(T, list_to_integer([H])),
	io:format("Const: ~w~n", [Const]),
	loop(L);
loop([H|T]) when ?is_letter(H) ->
	{L, Ident} = get_ident(T, [H]),
	io:format("Ident: ~p~n", [Ident]),
	Res = tables:find_sym(Ident),
	io:format("Letter: ~p~n", [Res]),
	loop(L);
loop([H|T]) when ?is_space(H) ->
	loop(T);
loop([H|T]) ->
	case tables:find_sym([H]) of
		{Class, Id} = Res -> io:format("Term: ~p~n", [Res]);
		error -> io:format("Unknown symbol~n", [])
	end,
	loop(T);
loop([])->
	ok.

get_const([H|T], Const) when ?is_digit(H) ->
	Int = list_to_integer([H]),
	get_const(T, Const*10 + Int);
get_const(L, Const) ->
	{L, Const}.

get_ident([H|T], Ident) when ?is_letter(H) ->
	get_ident(T, [H|Ident]);
get_ident(L, Ident) ->
	{L, lists:reverse(Ident)}.