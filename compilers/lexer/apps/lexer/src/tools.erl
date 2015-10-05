-module (tools).
-export ([is_digit/1, is_letter/1]).

is_digit(L) when is_list(L) ->
    Int = (catch erlang:list_to_integer(L)),
    is_number(Int).

is_letter(L) when is_number(L) and (L >= 65) and (L =< 90) ->
	true;
is_letter(L) when is_number(L) and (L >= 97) and (L =< 120) ->
	true;
is_letter(L) when is_number(L) ->
	false.