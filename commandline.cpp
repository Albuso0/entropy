#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include "commandline.h"

namespace std
{
	void CommandLine::Parse (int iargc, char *argv[])
	{
		int argc = iargc;
		for (argc--, argv++; argc > 0; argc--, argv++)
		{
			// remove "--" or "-" heading.
			std::string param = *argv;
			std::string::size_type cur = param.find ("--");
			if (cur == 0)
				param = param.substr (2, param.size () - 2);
			else
			{
				cur = param.find ("-");
				if (cur == 0)
					param = param.substr (1, param.size () - 1);
				else
					continue; // invalid argument. ignore.
			}
			// parse "name=value"
			cur = param.find ("=");
			std::string name, value;
			if (cur == std::string::npos)
			{
				name = param;
				value = "";
			}
			else
			{
				name = param.substr (0, cur);
				value = param.substr (cur + 1, param.size () - (cur+1));
			}
                        if (name == "PrintHelp" || name == "help" || name == "h")
                        {
                            // method below never returns.
                            PrintHelp (std::cout);
                            exit (0);
                        } 
			// read value
			for (Items::const_iterator i = m_items.begin (); i != m_items.end (); ++i)
			{
				if ((*i)->m_name == name)
				{
					if (!(*i)->Parse (value))
					{
						std::cerr << "Invalid argument value: "<< name << "=" << value << std::endl;
						PrintHelp (std::cerr);
						exit (1);
					}
				}
			}
		}
	}

	void CommandLine::PrintHelp (std::ostream &os) const
	{
		if (!m_items.empty ())
		{
			size_t width = 0;
			for (Items::const_iterator i = m_items.begin (); i != m_items.end (); ++i)
				width = std::max (width, (*i)->m_name.size ());
			width += 3;
			os << std::endl << "Program Arguments:" << std::endl;

			for (Items::const_iterator i = m_items.begin (); i != m_items.end (); ++i)
			{
				os << "    --"
				   << std::left << std::setw (width) << ( (*i)->m_name + ":")
				   << std::right << (*i)->m_help;
				
				// if ( (*i)->HasDefault ())
				// 	os << " [" << (*i)->GetDefault () << "]";
				os << std::endl;
			}
		}
	}
	
	CommandLine::~CommandLine ()
	{
		for (Items::const_iterator i = m_items.begin (); i != m_items.end (); ++i)
			delete *i;
		m_items.clear();
	}

}
