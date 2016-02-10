// Refer to CommandLine.h/cpp in NS3: 
// ns3::CommandLine Class Reference
// Basic version

#include <list>
#include <string>
#include <algorithm>
#include <sstream>
#include <ostream>


namespace std
{
	class CommandLine
	{
	public:
		CommandLine (){}
		~CommandLine ();
	
		template <typename T>
		void AddValue (const std::string &name, const std::string &help, T &value);
 
		void Parse (int argc, char *argv[]);
		void PrintHelp (std::ostream &os) const;
		
	private:
		class Item 
		{
		public:
			std::string m_name;       
			std::string m_help;
			virtual ~Item (){} 
			virtual bool Parse (const std::string value) = 0;
		};

		template <typename T>
		class UserItem : public Item
		{
		public:
			T *m_valuePtr;
			virtual bool Parse (const std::string value);
		};
 
		typedef std::list<Item *> Items;      
		Items m_items;                        
	}; 
   

	template <typename T>
	void CommandLine::AddValue (const std::string &name, const std::string &help, T &value)
	{
		UserItem<T> *item = new UserItem<T> ();
		item->m_name = name;
		item->m_help = help;
		item->m_valuePtr = &value;
     
		m_items.push_back (item);
	}

	template <typename T>
	bool CommandLine::UserItem<T>::Parse (const std::string value)
	{
		std::string src = value;
		std::transform(src.begin(), src.end(), src.begin(), ::tolower);
		std::istringstream iss;
		iss.str (src);
		iss >> (*m_valuePtr);
		return !iss.bad () && !iss.fail ();
	}

}
