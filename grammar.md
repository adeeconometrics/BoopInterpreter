program ::= [stmt] 

stmt ::= [expr] | [stmt::class] | [stmt::function] | 
		[stmt::loop] | [stmt::decision] | [stmt::var] | [stmt]

	stmt::class ::= type [id::class] -- > [supertype] -- {[stmt]}
	stmt::function ::= def [id::function] ([params]){ [stmt] }
	stmt::loop ::= while ([condition]) {[stmt]} | 
					for([init]; [condition]; [inc]) {[stmt]}
	stmt::decision ::= if([condition]) {[stmt]} | 
					if([condition]) {[stmt]} else {[stmt]} |
	stmt::var ::= [id::variable] = [expr]


