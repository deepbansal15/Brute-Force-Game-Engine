/*    ___  _________     ____          __         
     / _ )/ __/ ___/____/ __/___ ___ _/_/___ ___ 
    / _  / _// (_ //___/ _/ / _ | _ `/ // _ | -_)
   /____/_/  \___/    /___//_//_|_, /_//_//_|__/ 
                               /___/             

This file is part of the Brute-Force Game Engine, BFG-Engine

For the latest info, see http://www.brute-force-games.com

Copyright (c) 2011 Brute-Force Games GbR

The BFG-Engine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

The BFG-Engine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the BFG-Engine. If not, see <http://www.gnu.org/licenses/>.
*/

#include <set>
#include <string>

#include "Shared.h"

namespace EnumGen {

// $ cat Controller.h | head -n 25 | base64 -w 74 | perl -pe 's#(.+)#"$1"#g'
const static char DISCLAIMER[] =
"LyogICAgX19fICBfX19fX19fX18gICAgIF9fX18gICAgICAgICAgX18gICAgICAgICAKICAgIC"
"AvIF8gKS8gX18vIF9fXy9fX19fLyBfXy9fX18gX19fIF8vXy9fX18gX19fIAogICAgLyBfICAv"
"IF8vLyAoXyAvL19fXy8gXy8gLyBfIHwgXyBgLyAvLyBfIHwgLV8pCiAgIC9fX19fL18vICBcX1"
"9fLyAgICAvX19fLy9fLy9ffF8sIC9fLy9fLy9ffF9fLyAKICAgICAgICAgICAgICAgICAgICAg"
"ICAgICAgICAgIC9fX18vICAgICAgICAgICAgIAoKVGhpcyBmaWxlIGlzIHBhcnQgb2YgdGhlIE"
"JydXRlLUZvcmNlIEdhbWUgRW5naW5lLCBCRkctRW5naW5lCgpGb3IgdGhlIGxhdGVzdCBpbmZv"
"LCBzZWUgaHR0cDovL3d3dy5icnV0ZS1mb3JjZS1nYW1lcy5jb20KCkNvcHlyaWdodCAoYykgMj"
"AxMSBCcnV0ZS1Gb3JjZSBHYW1lcyBHYlIKClRoZSBCRkctRW5naW5lIGlzIGZyZWUgc29mdHdh"
"cmU6IHlvdSBjYW4gcmVkaXN0cmlidXRlIGl0IGFuZC9vciBtb2RpZnkKaXQgdW5kZXIgdGhlIH"
"Rlcm1zIG9mIHRoZSBHTlUgTGVzc2VyIEdlbmVyYWwgUHVibGljIExpY2Vuc2UgYXMgcHVibGlz"
"aGVkIGJ5CnRoZSBGcmVlIFNvZnR3YXJlIEZvdW5kYXRpb24sIGVpdGhlciB2ZXJzaW9uIDMgb2"
"YgdGhlIExpY2Vuc2UsIG9yCihhdCB5b3VyIG9wdGlvbikgYW55IGxhdGVyIHZlcnNpb24uCgpU"
"aGUgQkZHLUVuZ2luZSBpcyBkaXN0cmlidXRlZCBpbiB0aGUgaG9wZSB0aGF0IGl0IHdpbGwgYm"
"UgdXNlZnVsLApidXQgV0lUSE9VVCBBTlkgV0FSUkFOVFk7IHdpdGhvdXQgZXZlbiB0aGUgaW1w"
"bGllZCB3YXJyYW50eSBvZgpNRVJDSEFOVEFCSUxJVFkgb3IgRklUTkVTUyBGT1IgQSBQQVJUSU"
"NVTEFSIFBVUlBPU0UuICBTZWUgdGhlCkdOVSBMZXNzZXIgR2VuZXJhbCBQdWJsaWMgTGljZW5z"
"ZSBmb3IgbW9yZSBkZXRhaWxzLgoKWW91IHNob3VsZCBoYXZlIHJlY2VpdmVkIGEgY29weSBvZi"
"B0aGUgR05VIExlc3NlciBHZW5lcmFsIFB1YmxpYyBMaWNlbnNlCmFsb25nIHdpdGggdGhlIEJG"
"Ry1FbmdpbmUuIElmIG5vdCwgc2VlIDxodHRwOi8vd3d3LmdudS5vcmcvbGljZW5zZXMvPi4KKi"
"8K";

const static char TINKER_TOY[] =
"Ly8gby1vICBvLS1vIG8gICBvIG8tLW8gby0tbyAgICBPICBvLU8tbyBvLS1vIG8tbyAgICAgIC"
"AgIG8tbyAgby1vICBvLW8gICBvLS1vCi8vbyAgICAgfCAgICB8XCAgfCB8ICAgIHwgICB8ICAv"
"IFwgICB8ICAgfCAgICB8ICBcICAgICAgIC8gICAgbyAgIG8gfCAgXCAgfAovL3wgIC1vIE8tby"
"AgfCBcIHwgTy1vICBPLU9vICBvLS0tbyAgfCAgIE8tbyAgfCAgIE8gICAgIE8gICAgIHwgICB8"
"IHwgICBPIE8tbwovL28gICB8IHwgICAgfCAgXHwgfCAgICB8ICBcICB8ICAgfCAgfCAgIHwgIC"
"AgfCAgLyAgICAgICBcICAgIG8gICBvIHwgIC8gIHwKLy8gby1vICBvLS1vIG8gICBvIG8tLW8g"
"byAgIG8gbyAgIG8gIG8gICBvLS1vIG8tbyAgICAgICAgIG8tbyAgby1vICBvLW8gICBvLS1vCi"
"8vCg==";

const static char INFO_TEXT[] =
"/** @file\n"
"    This code has been generated by the BFG enum tool. If you modify this\n"
"    file, you'll most likely lose your changes. So don't commit *any*\n"
"    changes to this file and use the generator tool instead.\n"
"*/\n\n";

//! Provides functions for C++ code generation
namespace Generator
{
	namespace detail
	{
		//! Container type for "#includes" which doesn't allow duplicates.
		typedef std::set<std::string> UniqueIncludesT;

		//! Prepares Includes for the Generator
		/** Every Shared::Enum may have several include dependencies. Here
		    they get all collected into on std::set which removes duplicates,
		    for the sake of eliminating redundant include directives.
		*/
		void PrepareIncludes(UniqueIncludesT& Target,
		                     Shared::EnumVector& Everything)
		{
			Shared::EnumVector::const_iterator it = Everything.begin();

			for (; it != Everything.end(); ++it)
				std::copy(it->mMeta.Required.begin(),
				          it->mMeta.Required.end(),
				          std::inserter(Target, Target.end()));
		}
	} // namespace detail

	//! These are the functions which actually generate output.
	/** Each one requires at least one user provided std::string&.
	    Output will be written into that string. All functions
	    append at least one newline (LF) to the end of the output.
	    
	    A few functions have a Gen::Block parameter. This is necessary
	    where output can't be written in one single consecutive run.
	*/
	namespace Gen
	{
		enum Block
		{
			BEGIN,
			END
		};

		namespace detail
		{
			// decode-4.c from http://www.jeremie.com/frolic/base64
			int b64decode(char *s)
			{
				char *b64 = (char*)("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");
				int bit_offset, byte_offset, idx, i, n;
				unsigned char *d = (unsigned char *)s;
				char *p;
				n=i=0;
				while (*s && (p=strchr(b64,*s))) {
					idx = (int)(p - b64);
					byte_offset = (i*6)/8;
					bit_offset = (i*6)%8;
					d[byte_offset] &= ~((1<<(8-bit_offset))-1);
					if (bit_offset < 3) {
						 d[byte_offset] |= (idx << (2-bit_offset));
						 n = byte_offset+1;
					} else {
						 d[byte_offset] |= (idx >> (bit_offset-2));
						 d[byte_offset+1] = 0;
						d[byte_offset+1] |= (idx << (8-(bit_offset-2))) & 0xFF;
						 n = byte_offset+2;
					}
					s++; i++;
				}
				d[n] = 0;
				return n;
			}

			//! Replaces ':' by '_'
			std::string ReplaceNamespaces(const std::string& Input)
			{		
				std::string NoNS(Input);
				std::replace(NoNS.begin(), NoNS.end(), ':', '_');
				return NoNS;
			}

			//! Strips namespaces and leaves the most right part.			
			std::string StripNamespaces(const std::string& Input)
			{
				size_t LastColon = Input.find_last_of(':');
				
				if (LastColon == std::string::npos)
					return Input;
				else
					return Input.substr(LastColon + 1);
			}
		} // namespace detail

		//! Generates our license text and a nice "generated code"-warning.
		void Disclaimer(std::string& Result)
		{
			char Text[10240];
			strcpy(Text,DISCLAIMER);
			detail::b64decode(Text);
			Result += Text;
			
			strcpy(Text,TINKER_TOY);
			detail::b64decode(Text);
			Result += Text;

			Result += INFO_TEXT;
		}

		//! Generates a pretty safe include guard.
		void IncludeGuard(std::string& Result,
		                  std::string& inputFileCRC,
		                  Block b)
		{
			std::stringstream ss;
			if (b == BEGIN)
			{
				assert(! inputFileCRC.empty());
				
				ss << "#ifndef " << "_" << inputFileCRC << "_" << "\n"
				   << "#define " << "_" << inputFileCRC << "_" << "\n";
			}
			else
				ss << "#endif";
				
			ss << "\n";
				
			Result += ss.str();
		}
		
		//! Generates namespace blocks
		void Namespace(std::string& Result,
		               const std::string& Name,
		               Block b)
		{
			std::stringstream ss;
			
			if (b == BEGIN)
				ss << "namespace " << Name << (Name.empty()?"":" ") << "{\n";
			else
				ss << "} // namespace " << Name << "\n";
			
			ss << "\n";
			
			Result += ss.str();
		}

		//! Generates include preprocessor directives
		void Includes(std::string& Result,
		              const Generator::detail::UniqueIncludesT& Includes)
		{
			std::stringstream ss;

			Generator::detail::UniqueIncludesT::const_iterator it;
			
			for (it = Includes.begin(); it != Includes.end(); ++it)
				ss << "#include <" << *it << ">\n";
			
			ss << "\n";
			   
			Result += ss.str();
		}

		//! Generates a simple C++ enum definition
		void EnumList(std::string& Result, const Shared::Enum& Storage)
		{
			std::stringstream ss;
			
			ss << "enum " << Storage.mName << "\n"
			   << "{\n";
			   
			for (size_t i=0; i<Storage.mValues.size(); ++i)
			{
				ss << "\t" << Storage.mValues[i].Text;

				if (Storage.mValues[i].Set)
					ss << " = " << Storage.mValues[i].Set;
				
				// Append commata for each, except the last one.
				if (i != Storage.mValues.size() - 1)
					ss << ",";
					
				ss << "\n";
			}
			
			ss << "};\n";
			ss << "\n";
			
			Result += ss.str();
		}
		
		//! Generates assigned maps which contain serialisation data.
		void Map(std::string& Result,
		         const Shared::Enum& Storage,
		         bool SwapValues = false)
		{
			std::stringstream ss;

			// Container type			
			ss << "boost::unordered_map\n"
			   << "<\n";

			// Container definition
			if (SwapValues)
				ss << "\tstd::string,\n"
				   << "\t" << Storage.mName << "\n";
			else
				ss << "\t" << Storage.mName << ",\n"
				   << "\tstd::string\n";

			// Variable		
			std::string VarName = detail::ReplaceNamespaces(Storage.mName);

			ss << "> " << VarName;

			if (SwapValues)
				ss << "Str_ =\n";
			else
				ss << "Int_ =\n";
			
			// Assignments
			ss << "boost::assign::map_list_of\n";
			
			for (size_t i=0; i<Storage.mValues.size(); ++i)
			{
				const std::string& Ref = Storage.mValues[i].Text;
				std::string Stripped(detail::StripNamespaces(Ref));
				
				if (SwapValues)
					ss << "\t(\"" << Stripped << "\", "
					   << Ref << ")";
				else
					ss << "\t(" << Ref << ", \""
					   << Stripped << "\")"; // id, "id"

				// Append ';' to last statement.
				if (i == Storage.mValues.size() - 1)
					ss << ";";
					
				ss << "\n";
			}
			
			ss << "\n";

			Result += ss.str();	
		}
		
		//! Generates serialisation interface functions
		void Functions(std::string& Result,
		               const Shared::Enum& Storage,
		               bool DeclarationOnly)
		{
			std::stringstream ss;

			// Using a shorter reference for better readability.
			const std::string& Ref = Storage.mName;
			const std::string& Stripped = detail::ReplaceNamespaces(Ref);

			if (! DeclarationOnly)
			{
				// First function: Get string by enum
				// -> Doxygen
				ss << "//! Interface function for std::string => " << Ref
				   << " conversion.\n";
				   
				ss << "//! \\return Enum-identifier as std::string.\n";
				ss << "//! \\exception std::out_of_range if no such element"
					  " is present.\n";
			}

			// -> Function definition
			if (DeclarationOnly)
				ss << Storage.mMeta.Export << " ";

			ss << "const std::string& asStr"
			   << "(" << Ref << " value)";

			if (DeclarationOnly)
				ss << ";\n";
			else
			{
				// -> Function body (see Gen::Map) with exception re-throw
				ss << "\n{\n"
				   << "\ttry\n"
				   << "\t{\n"
					   << "\t\treturn " << Stripped << "Int_.at(value);\n"
				   << "\t}\n"

				   << "\tcatch (std::out_of_range&)\n"
				   << "\t{\n"
					   << "\t\tstd::stringstream ss;\n"
					   << "\t\tss << \"Conversion of enum " << Ref << "(\"\n"
					   << "\t\t   << static_cast<int>(value)\n"
					   << "\t\t   << \") to string failed!\";\n"
					   << "\t\tthrow std::out_of_range(ss.str());\n"
				   << "\t}\n";

				ss << "}\n"
				   << "\n";
			}

			if (! DeclarationOnly)
			{
				// Second function: Get enum by string
				// -> Doxygen
				ss << "//! Interface function for " << Ref
				   << " => std::string conversion.\n";
				   
				ss << "//! \\return Enum-identifier as " << Ref << ".\n";
				ss << "//! \\exception std::out_of_range if no such element"
					  " is present.\n";
			}

			// -> Function definition
			if (DeclarationOnly)
				ss << Storage.mMeta.Export << " ";
			
			ss << Ref << " as" << detail::StripNamespaces(Ref)
			   << "(const std::string& value)";

			if (DeclarationOnly)
				ss << ";\n";
			else
			{
				// -> Function body (see Gen::Map) with exception re-throw
				ss << "\n{\n"
				   << "\ttry\n"
				   << "\t{\n"
					   << "\t\treturn " << Stripped << "Str_.at(value);\n"
				   << "\t}\n"

				   << "\tcatch (std::out_of_range&)\n"
				   << "\t{\n"
					   << "\t\tstd::stringstream ss;\n"
					   << "\t\tss << \"Conversion of string \\\"\" << value\n"
					   << "\t\t   << \"\\\" to enum " << Ref << " failed!\";\n"
					   << "\t\tthrow std::out_of_range(ss.str());\n"
				   << "\t}\n";
				   
				ss << "}\n"
				   << "\n";
			}
			Result += ss.str();
			Result += "\n";
		}
			
		//! Generates a nice separator comment (one line)
		void Separator(std::string& Result, std::string::value_type sign)
		{
			Result += "// ";
			Result += std::string(76, sign);
			Result += "\n\n";
		}
		
		//! Used to disable annoying Visual Studio warnings
		void Pragmas(std::string& Result, Block b)
		{
			Result += "#ifdef _MSC_VER\n";
			if (b == BEGIN)
			{
				Result += "  #pragma warning (push)\n";
				Result += "  #pragma warning (disable:4512) // "
						  "\"assignment operator could not be generated\"\n";
			}
			else
			{
				Result += "  #pragma warning (pop)\n";
			}
			Result += "#endif\n";
			Result += "\n";
		}
		
		//! EnumGen code doesn't need to be covered by tests! :)
		void LcovExclude(std::string& Result, Block b)
		{
			if (b == BEGIN)
				Result += "// LCOV_EXCL_START";
			else
				Result += "// LCOV_EXCL_STOP";
			Result += "\n\n";
		}
	}

	//! Generates enums and their serialisation functions in
	//! header-only style.
	//!
	//! \param[out] Result The generated result which may be written
	//!                    into a file afterwards.
	//! \param[in] inputFileCRC The CRC of the input XML file. This 
	//!                         may be generated by calling calculateFileCRC().
	//! \param[in] Everything Should contain the whole parsed content 
	//!                       of one XML file. 
	void MakeHeaderOnly(std::string& Result,
	                    std::string& inputFileCRC,
	                    Shared::EnumVector& Everything)
	{
		detail::UniqueIncludesT Inc;
		detail::PrepareIncludes(Inc, Everything);

		// Standard includes.
		Inc.insert("sstream");
		Inc.insert("boost/unordered_map.hpp");
		Inc.insert("boost/assign/list_of.hpp");
	
		Gen::Disclaimer(Result);

		Gen::IncludeGuard(Result, inputFileCRC, Gen::BEGIN);
		Gen::Pragmas(Result, Gen::BEGIN);
		Gen::Includes(Result, Inc);
		Gen::LcovExclude(Result, Gen::BEGIN);

		Shared::EnumVector::const_iterator it = Everything.begin();

		for (; it != Everything.end(); ++it)
		{
			// Open user-namespace (if there's one)
			if (! it->mMeta.Namespace.empty())
				Gen::Namespace(Result, it->mMeta.Namespace, Gen::BEGIN);

			Gen::Namespace(Result, "ID", Gen::BEGIN);

			if (! it->mMeta.DefinitionExists)
				Gen::EnumList(Result, *it);     // enum Name { ... };

			// The maps and functions need to be in an anonymous namespace
			// in order to prevent multiple declarations. But not the enums
			// themselves because doing so may cause strange linker errors
			// when using MSVC.
			
			Gen::Namespace(Result, "", Gen::BEGIN);

			Gen::Map(Result, *it, false);       // Enum <=> String
			Gen::Map(Result, *it, true);        // String <=> Enum

			Gen::Functions(Result, *it, false); // asStr() and asEnum()

			Gen::Namespace(Result, "anonymous-namespace", Gen::END);

			Gen::Namespace(Result, "ID", Gen::END);

			// Close user-namespace (if there's one)
			if (! it->mMeta.Namespace.empty())
				Gen::Namespace(Result, it->mMeta.Namespace, Gen::END);
		
			if (it + 1 != Everything.end())
				Gen::Separator(Result, '#');
		}

		Gen::LcovExclude(Result, Gen::END);
		Gen::Pragmas(Result, Gen::END);
		Gen::IncludeGuard(Result, inputFileCRC, Gen::END);
	}
	
	//! Generates enums and their serialisation functions seperated
	//! in header and source files. This usually leds to faster compile
	//! times, but you may need to make EnumGen export some functions.
	//!
	//! \param[out] resultHeader The generated header result which
	//!                          may be written into a file afterwards.
	//! \param[out] resultSource The generated source result which
	//!                          may be written into a file afterwards.
	//! \param[in] headerFilename Must be known, since the generated source
	//!                           file needs to include the generated header. 
	//! \param[in] inputFileCRC The CRC of the input XML file. This 
	//!                         may be generated by calling calculateFileCRC().
	//! \param[in] Everything Should contain the whole parsed content 
	//!                       of one XML file. 
	void MakePair(std::string& resultHeader,
	              std::string& resultSource,
	              const std::string& headerFilename,
	              std::string& inputFileCRC,
	              Shared::EnumVector& Everything)
	{
		Gen::Disclaimer(resultHeader);
		Gen::Disclaimer(resultSource);
		
		Gen::IncludeGuard(resultHeader, inputFileCRC, Gen::BEGIN);

		Gen::Pragmas(resultSource, Gen::BEGIN);

		detail::UniqueIncludesT IncSource;
		resultSource += "#include \"" + headerFilename + "\"" + "\n";
		IncSource.insert("sstream");
		IncSource.insert("boost/unordered_map.hpp");
		IncSource.insert("boost/assign/list_of.hpp");
		Gen::Includes(resultSource, IncSource);
		Gen::LcovExclude(resultSource, Gen::BEGIN);

		detail::UniqueIncludesT IncHeader;
		IncHeader.insert("string");
		detail::PrepareIncludes(IncHeader, Everything);
		Gen::Includes(resultHeader, IncHeader);
		Gen::LcovExclude(resultHeader, Gen::BEGIN);
		
		Shared::EnumVector::const_iterator it = Everything.begin();

		for (; it != Everything.end(); ++it)
		{
			std::string LastNamespace;

			if (! it->mMeta.Namespace.empty())
			{
				Gen::Namespace(resultHeader, it->mMeta.Namespace, Gen::BEGIN);
				Gen::Namespace(resultSource, it->mMeta.Namespace, Gen::BEGIN);
			}

			Gen::Namespace(resultHeader, "ID", Gen::BEGIN);
			Gen::Namespace(resultSource, "ID", Gen::BEGIN);

			if (! it->mMeta.DefinitionExists)
				Gen::EnumList(resultHeader, *it);     // enum Name { ... };

			Gen::Map(resultSource, *it, false);       // Enum <=> String
			Gen::Map(resultSource, *it, true);        // String <=> Enum

			Gen::Functions(resultHeader, *it, true);  // asStr() and asEnum()
			Gen::Functions(resultSource, *it, false); // asStr() and asEnum()

			if (it + 1 != Everything.end())
				Gen::Separator(resultSource, '#');

			Gen::Namespace(resultHeader, "ID", Gen::END);
			Gen::Namespace(resultSource, "ID", Gen::END);

			if (! it->mMeta.Namespace.empty())
			{
				Gen::Namespace(resultHeader, it->mMeta.Namespace, Gen::END);
				Gen::Namespace(resultSource, it->mMeta.Namespace, Gen::END);
			}
		}
		
		Gen::LcovExclude(resultSource, Gen::END);
		Gen::LcovExclude(resultHeader, Gen::END);

		Gen::Pragmas(resultSource, Gen::END);
		
		Gen::IncludeGuard(resultHeader, inputFileCRC, Gen::END);
	}
}

} // namespace EnumGen

