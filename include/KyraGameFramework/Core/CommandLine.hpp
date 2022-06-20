#ifndef KYRAGAMEFRAMEWORK_CORE_COMMANDLINE_HPP
#define KYRAGAMEFRAMEWORK_CORE_COMMANDLINE_HPP

#include <KyraGameFramework/Core/CmdParameterValue.hpp>
#include <string>
#include <map>


namespace kyra {
	namespace core {
		
		/// Parses the command line and provides functions to check and access the values of the parameters
		class KYRA_CORE_API CommandLine {

			std::string m_ExecutableName; 						//!< The name of the executable
			std::map<std::string,CmdParameterValue> m_Parameters;	//!< Holding all the parameters and their values
			
			public:
			/// Default constructor
			CommandLine();

			/// Default destructor
			~CommandLine();
			
			/*** Parses the commandline
				 \param the number of arguments provided to the executable
				 \param the array containting all the parameters 
				 \return true if the commandline was succesfully parsed, false if there was en error */
			bool parse(int argc, char** argv);
			
			/*** Checks if a parameter is set
				 \return true if the parameter is set, false if the parameter is not set */
			bool isSet(const std::string& id) const;
			
			/*** Returns the Parameter
				 \param the id of the parameter
				 \return the value of the parameter */
			CmdParameterValue getValue(const std::string& id);
			
			/*** Returns the name of the executable
				 \return The name of the executable */
			std::string getExecutableName() const;
			
		};
		
	}
}

#endif