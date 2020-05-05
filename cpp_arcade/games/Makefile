all:
	$(MAKE) -C ./nibbler/
	$(MAKE) -C ./pacman/

clean:
	$(MAKE) -C ./nibbler/ clean
	$(MAKE) -C ./pacman/ clean

fclean: clean
	$(MAKE) -C ./nibbler/ fclean
	$(MAKE) -C ./pacman/ fclean

re: fclean all

.PHONY: all clean fclean re