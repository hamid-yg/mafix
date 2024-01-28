all: run_client run_server

run_client:
	@make -C client
	@cp client/_client .

run_server:
	@make -C server
	@cp server/_server .

fclean:
	@make fclean -C client
	@make fclean -C server
	@rm -f _client _server

re: fclean all
