#ifndef _META_REGLE_H_
#define _META_REGLE_H_
#endif
//condtion of the meta_regle 
struct MetaCondition{

	std::string subject;
	std::string mark; 
			
};

class MetaRegle{

	private: 
		
		std::string regle_name;
		//the vector which contains the conditions of meta_regle
		std::vector<MetaCondition> conditions;
		std::string result;
	
	public:
		MetaRegle(){};
	    ~MetaRegle(){};
		void set_regle_name(const std::string _regle_name){regle_name = _regle_name;}
		void set_condition(const MetaCondition condition){conditions.push_back(condition);}
		void set_result(const std::string _result){result = _result;}
		void get_condition(std::vector<MetaCondition> &_conditions){_conditions = conditions;}
		void get_result(std::string &_result){_result = result;}

};