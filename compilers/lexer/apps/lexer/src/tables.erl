-module (tables).
-include ("tables.hrl").
-include_lib("stdlib/include/ms_transform.hrl").

-export ([init/0, find_sym/1, add_id/2]).

-define (SYMTABLE, symTable).
-define (IDTABLE, idTable).

init() ->
	ets:new(?SYMTABLE, [named_table, {keypos, #sym_t.sym}]),
	ets:new(?IDTABLE, [named_table, {keypos, #id_t.id}]),
	fill_sym().

fill_sym() ->
	%ets:insert(?SYMTABLE, #sym_t{id = 100, sym = "-", class = unary}),

	ets:insert(?SYMTABLE, #sym_t{id = 101, sym = "*", class = muldiv}),
	ets:insert(?SYMTABLE, #sym_t{id = 102, sym = "/", class = muldiv}),

	ets:insert(?SYMTABLE, #sym_t{id = 103, sym = "+", class = plsub}),
	ets:insert(?SYMTABLE, #sym_t{id = 104, sym = "-", class = plsub}),

	ets:insert(?SYMTABLE, #sym_t{id = 105, sym = "Var", class = kw}),

	ets:insert(?SYMTABLE, #sym_t{id = 106, sym = ".", class = term}),
	ets:insert(?SYMTABLE, #sym_t{id = 107, sym = ",", class = term}),
	ets:insert(?SYMTABLE, #sym_t{id = 108, sym = "(", class = bracket}),
	ets:insert(?SYMTABLE, #sym_t{id = 109, sym = ")", class = bracket}),

	ets:insert(?SYMTABLE, #sym_t{id = 110, sym = "=", class = assign}).

% Поиск символа в таблице
find_sym(Sym) ->
	case ets:select(?SYMTABLE, ets:fun2ms(fun(N = #sym_t{id=Id,sym=S,class=C}) 
								   when S==Sym -> {C, Id} end)) of
		[{Class, Id}] -> {Class, Id};
		[] -> error
	end.

% Добавление идентификатора в таблицу идентификаторов
add_id(Name, LastId) ->
	case ets:select(?IDTABLE, ets:fun2ms(fun(#id_t{id=Id,name=N}) 
								   when N==Name -> Id end)) of
		[Id] -> [{current, Id}, {lastId, LastId}];
		[] -> 
			NewId = LastId + 1,
			ets:insert(?IDTABLE, #id_t{id = NewId, name = Name}),
			[{current, NewId}, {lastId, NewId}]
	end.