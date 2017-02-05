void	*get_arg_direct(t_map *tmap, int opcode)
{

}

int		get_size_arg(int opcode, int *arg_byte)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (!(op_tab[opcode - 1].num_bytecode))
	{
		if (opcode == OP_LIVE + 1)
			return (4);
		else if (opcode == OP_ZJMP + 1)
			return (2);
		else	//(opcode == OP_FORK || opcode == OP_LFORK)
			return (2);
	}
	while (i < op_tab[opcode - 1].num_arg)
	{
		if (arg_byte[i] == T_DIR && !(op_tab[opcode - 1].as_address))
			ret += 4;
		else if (arg_byte[i] == T_DIR)
			ret += 2;
		else if (arg_byte[i] == T_IND)
			ret += 2;
		else if (arg_byte[i] == T_REG)
			ret += 1;
		i++;
	}
	return (ret);
}
