LOAD_ROM_0 0x0000 0x20000
{
	EXEC_ROM_0 0x0000 0x10000
	{
        init.o ( +ENTRY, +FIRST )
		* ( +RO )
	}

	RAM 0x10000 0x10000
	{
		* ( +RW , +ZI )
	}
}
