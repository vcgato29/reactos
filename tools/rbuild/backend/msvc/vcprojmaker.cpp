/*
 * Copyright (C) 2002 Patrik Stridvall
 * Copyright (C) 2005 Royce Mitchell III
 * Copyright (C) 2006 Herv� Poussineau
 * Copyright (C) 2006 Christoph von Wittich
 * Copyright (C) 2009 Ged Murphy
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef _MSC_VER
#pragma warning ( disable : 4786 )
#endif//_MSC_VER

#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <stdio.h>

#include "msvc.h"

using std::string;
using std::vector;
using std::set;

typedef set<string> StringSet;

#ifdef OUT
#undef OUT
#endif//OUT

struct SortFilesAscending
{
	bool operator()(const string& rhs, const string& lhs)
	{
		return rhs < lhs;
	}
};


VCProjMaker::VCProjMaker ( )
{
	vcproj_file = "";
}

VCProjMaker::VCProjMaker ( Configuration& buildConfig,
						   const std::vector<MSVCConfiguration*>& msvc_configs,
						   std::string filename )
{
	configuration = buildConfig;
	m_configurations = msvc_configs;
	vcproj_file = filename;

	OUT = fopen ( vcproj_file.c_str(), "wb" );

	if ( !OUT )
	{
		printf ( "Could not create file '%s'.\n", vcproj_file.c_str() );
	}
}

VCProjMaker::~VCProjMaker()
{
	fclose ( OUT );
}

void
VCProjMaker::_generate_proj_file ( const Module& module )
{
	size_t i;

	string computername;
	string username;

	// make sure the containers are empty
	header_files.clear();
	includes.clear();
	includes_ros.clear();
	libraries.clear();
	common_defines.clear();

	if (getenv ( "USERNAME" ) != NULL)
		username = getenv ( "USERNAME" );
	if (getenv ( "COMPUTERNAME" ) != NULL)
		computername = getenv ( "COMPUTERNAME" );
	else if (getenv ( "HOSTNAME" ) != NULL)
		computername = getenv ( "HOSTNAME" );

	string vcproj_file_user = "";

	if ((computername != "") && (username != ""))
		vcproj_file_user = vcproj_file + "." + computername + "." + username + ".user";

	printf ( "Creating MSVC.NET project: '%s'\n", vcproj_file.c_str() );

	string path_basedir = module.GetPathToBaseDir ();
	string intenv = Environment::GetIntermediatePath ();
	string outenv = Environment::GetOutputPath ();
	string outdir;
	string intdir;
	string vcdir;

	if ( intenv == "obj-i386" )
		intdir = path_basedir + "obj-i386"; /* append relative dir from project dir */
	else
		intdir = intenv;

	if ( outenv == "output-i386" )
		outdir = path_basedir + "output-i386";
	else
		outdir = outenv;

	if ( configuration.UseVSVersionInPath )
	{
		vcdir = DEF_SSEP + _get_vc_dir();
	}

	bool include_idl = false;

	vector<string> source_files, resource_files;
	vector<const IfableData*> ifs_list;
	ifs_list.push_back ( &module.project.non_if_data );
	ifs_list.push_back ( &module.non_if_data );

	while ( ifs_list.size() )
	{
		const IfableData& data = *ifs_list.back();
		ifs_list.pop_back();
		const vector<File*>& files = data.files;
		for ( i = 0; i < files.size(); i++ )
		{
			if (files[i]->file.directory != SourceDirectory)
				continue;

			// We want the full path here for directory support later on
			string path = Path::RelativeFromDirectory (
				files[i]->file.relative_path,
				module.output->relative_path );
			string file = path + std::string("\\") + files[i]->file.name;

			if ( !stricmp ( Right(file,3).c_str(), ".rc" ) )
				resource_files.push_back ( file );
			else if ( !stricmp ( Right(file,2).c_str(), ".h" ) )
				header_files.push_back ( file );
			else
				source_files.push_back ( file );
		}
		const vector<Include*>& incs = data.includes;
		for ( i = 0; i < incs.size(); i++ )
		{
			string path = Path::RelativeFromDirectory (
				incs[i]->directory->relative_path,
				module.output->relative_path );
			if ( module.type != RpcServer && module.type != RpcClient )
			{
				if ( path.find ("/include/reactos/idl") != string::npos)
				{
					include_idl = true;
					continue;
				}
			}
			// switch between general headers and ros headers
			if ( !strncmp(incs[i]->directory->relative_path.c_str(), "include\\crt", 11 ) ||
			     !strncmp(incs[i]->directory->relative_path.c_str(), "include\\ddk", 11 ) ||
			     !strncmp(incs[i]->directory->relative_path.c_str(), "include\\GL", 10 ) ||
			     !strncmp(incs[i]->directory->relative_path.c_str(), "include\\psdk", 12 ) ||
			     !strncmp(incs[i]->directory->relative_path.c_str(), "include\\reactos\\wine", 20 ) )
			{
				if (strncmp(incs[i]->directory->relative_path.c_str(), "include\\crt", 11 ))
					// not crt include
					includes_ros.push_back ( path );
			}
			else
			{
				includes.push_back ( path );
			}
		}
		const vector<Library*>& libs = data.libraries;
		for ( i = 0; i < libs.size(); i++ )
		{
			string libpath = outdir + "\\" + libs[i]->importedModule->output->relative_path + "\\" + _get_vc_dir() + "\\---\\" + libs[i]->name + ".lib";
			libraries.push_back ( libpath );
		}
		const vector<Define*>& defs = data.defines;
		for ( i = 0; i < defs.size(); i++ )
		{
			if ( defs[i]->backend != "" && defs[i]->backend != "msvc" )
				continue;

			if ( defs[i]->value[0] )
				common_defines.insert( defs[i]->name + "=" + defs[i]->value );
			else
				common_defines.insert( defs[i]->name );
		}
		for ( std::map<std::string, Property*>::const_iterator p = data.properties.begin(); p != data.properties.end(); ++ p )
		{
			Property& prop = *p->second;
			if ( strstr ( module.baseaddress.c_str(), prop.name.c_str() ) )
				baseaddr = prop.value;
		}
	}
	/* include intermediate path for reactos.rc */
	string version = intdir + "\\include";
	includes.push_back (version);
	version += "\\reactos";
	includes.push_back (version);

	string include_string;

	fprintf ( OUT, "<?xml version=\"1.0\" encoding = \"Windows-1252\"?>\r\n" );
	fprintf ( OUT, "<VisualStudioProject\r\n" );
	fprintf ( OUT, "\tProjectType=\"Visual C++\"\r\n" );

	if (configuration.VSProjectVersion.empty())
		configuration.VSProjectVersion = MS_VS_DEF_VERSION;

	fprintf ( OUT, "\tVersion=\"%s\"\r\n", configuration.VSProjectVersion.c_str() );
	fprintf ( OUT, "\tName=\"%s\"\r\n", module.name.c_str() );
	fprintf ( OUT, "\tProjectGUID=\"%s\"\r\n", module.guid.c_str() );
	fprintf ( OUT, "\tKeyword=\"Win32Proj\">\r\n" );

	fprintf ( OUT, "\t<Platforms>\r\n" );
	fprintf ( OUT, "\t\t<Platform\r\n" );
	fprintf ( OUT, "\t\t\tName=\"Win32\"/>\r\n" );
	fprintf ( OUT, "\t</Platforms>\r\n" );

	// Set the binary type
	string module_type = GetExtension(*module.output);
	BinaryType binaryType;
	if ((module.type == ObjectLibrary) || (module.type == RpcClient) ||(module.type == RpcServer) || (module_type == ".lib") || (module_type == ".a"))
		binaryType = Lib;
	else if ((module_type == ".dll") || (module_type == ".cpl"))
		binaryType = Dll;
	else if ((module_type == ".exe") || (module_type == ".scr"))
		binaryType = Exe;
	else if (module_type == ".sys")
		binaryType = Sys;
	else
		binaryType = BinUnknown;

	// Write out all the configurations
	fprintf ( OUT, "\t<Configurations>\r\n" );
	for ( size_t icfg = 0; icfg < m_configurations.size(); icfg++ )
	{
		const MSVCConfiguration& cfg = *m_configurations[icfg];

		if ( cfg.optimization == RosBuild )
		{
			_generate_makefile_configuration( module, cfg );
		}
		else
		{
			_generate_standard_configuration( module, cfg, binaryType );
		}
	}
	fprintf ( OUT, "\t</Configurations>\r\n" );

	// Write out the project files
	fprintf ( OUT, "\t<Files>\r\n" );

	// Source files
	fprintf ( OUT, "\t\t<Filter\r\n" );
	fprintf ( OUT, "\t\t\tName=\"Source Files\"\r\n" );
	fprintf ( OUT, "\t\t\tFilter=\"cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;S\">\r\n" );

	std::sort(source_files.begin(), source_files.end(), SortFilesAscending());
	vector<string> last_folder;
	vector<string> split_path;
	string indent_tab("\t\t\t");

	for ( size_t isrcfile = 0; isrcfile < source_files.size(); isrcfile++ )
	{
		string source_file = DosSeparator(source_files[isrcfile]);

		Path::Split(split_path, source_file, false);
		size_t same_folder_index = 0;
		for ( size_t ifolder = 0; ifolder < last_folder.size(); ifolder++ )
		{
			if ( ifolder < split_path.size() && last_folder[ifolder] == split_path[ifolder] )
				++same_folder_index;
			else
				break;
		}

		if ( same_folder_index < split_path.size() || last_folder.size() > split_path.size() )
		{
			int tabStart = 1;
			if ( split_path.size() > last_folder.size() )
			{
				for ( size_t ifolder = last_folder.size(); ifolder < split_path.size(); ifolder++ )
					indent_tab.push_back('\t');
				tabStart = split_path.size() - last_folder.size() + 1;
			}
			else if ( split_path.size() < last_folder.size() )
			{
				indent_tab.resize( split_path.size() + 3 );
				tabStart = split_path.size() - last_folder.size() + 1;
			}

			for ( size_t ifolder = last_folder.size(), itab = tabStart; ifolder > same_folder_index; ifolder--, itab++ )
			{
				fprintf ( OUT, "%s</Filter>\r\n", indent_tab.substr(0, indent_tab.size() - itab).c_str() );
			}

			for ( size_t ifolder = same_folder_index, itab = split_path.size() - same_folder_index; ifolder < split_path.size(); ifolder++, itab-- )
			{
				const string tab = indent_tab.substr(0, indent_tab.size() - itab);
				fprintf ( OUT, "%s<Filter\r\n", tab.c_str() );
				fprintf ( OUT, "%s\tName=\"%s\">\r\n", tab.c_str(), split_path[ifolder].c_str() );
			}

			last_folder = split_path;
		}

		fprintf ( OUT, "%s<File\r\n", indent_tab.c_str() );
		fprintf ( OUT, "%s\tRelativePath=\"%s\">\r\n", indent_tab.c_str(), source_file.c_str() );

		for ( size_t iconfig = 0; iconfig < m_configurations.size(); iconfig++ )
		{
			const MSVCConfiguration& config = *m_configurations[iconfig];

			if (( isrcfile == 0 ) && ( module.pch != NULL ))
			{
				/* little hack to speed up PCH */
				fprintf ( OUT, "%s\t<FileConfiguration\r\n", indent_tab.c_str() );
				fprintf ( OUT, "%s\t\tName=\"", indent_tab.c_str() );
				fprintf ( OUT, config.name.c_str() );
				fprintf ( OUT, "|Win32\">\r\n" );
				fprintf ( OUT, "%s\t\t<Tool\r\n", indent_tab.c_str() );
				fprintf ( OUT, "%s\t\t\tName=\"VCCLCompilerTool\"\r\n", indent_tab.c_str() );
				fprintf ( OUT, "%s\t\t\tUsePrecompiledHeader=\"1\"/>\r\n", indent_tab.c_str() );
				fprintf ( OUT, "%s\t</FileConfiguration>\r\n", indent_tab.c_str() );
			}

			//if (configuration.VSProjectVersion < "8.00") {
				if ((source_file.find(".idl") != string::npos) || ((source_file.find(".asm") != string::npos || tolower(source_file.at(source_file.size() - 1)) == 's')))
				{
					fprintf ( OUT, "%s\t<FileConfiguration\r\n", indent_tab.c_str() );
					fprintf ( OUT, "%s\t\tName=\"", indent_tab.c_str() );
					fprintf ( OUT, config.name.c_str() );
					fprintf ( OUT, "|Win32\">\r\n" );
					fprintf ( OUT, "%s\t\t<Tool\r\n", indent_tab.c_str() );
					if (source_file.find(".idl") != string::npos)
					{
						string src = source_file.substr (0, source_file.find(".idl"));

						if ( src.find (".\\") != string::npos )
							src.erase (0, 2);

						fprintf ( OUT, "%s\t\t\tName=\"VCCustomBuildTool\"\r\n", indent_tab.c_str() );

						if ( module.type == RpcClient )
						{
							fprintf ( OUT, "%s\t\t\tCommandLine=\"midl.exe /cstub %s_c.c /header %s_c.h /server none &quot;$(InputPath)&quot; /out &quot;$(IntDir)&quot;", indent_tab.c_str(), src.c_str (), src.c_str () );
							fprintf ( OUT, "&#x0D;&#x0A;");
							fprintf ( OUT, "cl.exe /Od /D &quot;WIN32&quot; /D &quot;_DEBUG&quot; /D &quot;_WINDOWS&quot; /D &quot;_WIN32_WINNT=0x502&quot; /D &quot;_UNICODE&quot; /D &quot;UNICODE&quot; /Gm /EHsc /RTC1 /MDd /Fo&quot;$(IntDir)\\%s.obj&quot; /W3 /c /Wp64 /ZI /TC &quot;$(IntDir)\\%s_c.c&quot; /nologo /errorReport:prompt", src.c_str (), src.c_str () );
						}
						else
						{
							fprintf ( OUT, "%s\t\t\tCommandLine=\"midl.exe /sstub %s_s.c /header %s_s.h /client none &quot;$(InputPath)&quot; /out &quot;$(IntDir)&quot;", indent_tab.c_str(), src.c_str (), src.c_str () );
							fprintf ( OUT, "&#x0D;&#x0A;");
							fprintf ( OUT, "cl.exe /Od /D &quot;WIN32&quot; /D &quot;_DEBUG&quot; /D &quot;_WINDOWS&quot; /D &quot;_WIN32_WINNT=0x502&quot; /D &quot;_UNICODE&quot; /D &quot;UNICODE&quot; /Gm /EHsc /RTC1 /MDd /Fo&quot;$(IntDir)\\%s.obj&quot; /W3 /c /Wp64 /ZI /TC &quot;$(IntDir)\\%s_s.c&quot; /nologo /errorReport:prompt", src.c_str (), src.c_str () );

						}
						fprintf ( OUT, "&#x0D;&#x0A;");
						fprintf ( OUT, "lib.exe /OUT:&quot;$(OutDir)\\%s.lib&quot; &quot;$(IntDir)\\%s.obj&quot;&#x0D;&#x0A;\"\r\n", module.name.c_str (), src.c_str () );
						fprintf ( OUT, "%s\t\t\tOutputs=\"$(IntDir)\\$(InputName).obj\"/>\r\n", indent_tab.c_str() );
					}
					else if ((source_file.find(".asm") != string::npos))
					{
						fprintf ( OUT, "%s\t\t\tName=\"VCCustomBuildTool\"\r\n", indent_tab.c_str() );
						fprintf ( OUT, "%s\t\t\tCommandLine=\"nasmw $(InputPath) -f coff -o &quot;$(OutDir)\\$(InputName).obj&quot;\"\r\n", indent_tab.c_str() );
						fprintf ( OUT, "%s\t\t\tOutputs=\"$(OutDir)\\$(InputName).obj\"/>\r\n", indent_tab.c_str() );
					}
					else if ((tolower(source_file.at(source_file.size() - 1)) == 's'))
					{
						fprintf ( OUT, "%s\t\t\tName=\"VCCustomBuildTool\"\r\n", indent_tab.c_str() );
						fprintf ( OUT, "%s\t\t\tCommandLine=\"cl /E &quot;$(InputPath)&quot; %s /D__ASM__ | as -o &quot;$(OutDir)\\$(InputName).obj&quot;\"\r\n", indent_tab.c_str(), include_string.c_str() );
						fprintf ( OUT, "%s\t\t\tOutputs=\"$(OutDir)\\$(InputName).obj\"/>\r\n", indent_tab.c_str() );
					}
					fprintf ( OUT, "%s\t</FileConfiguration>\r\n", indent_tab.c_str() );
				}
			//}
		}
		fprintf ( OUT, "%s</File>\r\n", indent_tab.c_str() );
	}

	for ( size_t ifolder = last_folder.size(); ifolder > 0; ifolder-- )
	{
		indent_tab.resize( ifolder + 2 );
		fprintf ( OUT, "%s</Filter>\r\n", indent_tab.c_str() );
	}

	fprintf ( OUT, "\t\t</Filter>\r\n" );

	// Header files
	fprintf ( OUT, "\t\t<Filter\r\n" );
	fprintf ( OUT, "\t\t\tName=\"Header Files\"\r\n" );
	fprintf ( OUT, "\t\t\tFilter=\"h;hpp;hxx;hm;inl\">\r\n" );
	for ( i = 0; i < header_files.size(); i++ )
	{
		const string& header_file = header_files[i];
		fprintf ( OUT, "\t\t\t<File\r\n" );
		fprintf ( OUT, "\t\t\t\tRelativePath=\"%s\">\r\n", header_file.c_str() );
		fprintf ( OUT, "\t\t\t</File>\r\n" );
	}
	fprintf ( OUT, "\t\t</Filter>\r\n" );

	// Resource files
	fprintf ( OUT, "\t\t<Filter\r\n" );
	fprintf ( OUT, "\t\t\tName=\"Resource Files\"\r\n" );
	fprintf ( OUT, "\t\t\tFilter=\"ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe\">\r\n" );
	for ( i = 0; i < resource_files.size(); i++ )
	{
		const string& resource_file = resource_files[i];
		fprintf ( OUT, "\t\t\t<File\r\n" );
		fprintf ( OUT, "\t\t\t\tRelativePath=\"%s\">\r\n", resource_file.c_str() );
		fprintf ( OUT, "\t\t\t</File>\r\n" );
	}
	fprintf ( OUT, "\t\t</Filter>\r\n" );

	fprintf ( OUT, "\t</Files>\r\n" );
	fprintf ( OUT, "\t<Globals>\r\n" );
	fprintf ( OUT, "\t</Globals>\r\n" );
	fprintf ( OUT, "</VisualStudioProject>\r\n" );
}

void VCProjMaker::_generate_user_configuration ()
{
	// Call base implementation
	ProjMaker::_generate_user_configuration ();
}

void VCProjMaker::_generate_standard_configuration( const Module& module,
													const MSVCConfiguration& cfg,
													BinaryType binaryType )
{
	string path_basedir = module.GetPathToBaseDir ();
	string intenv = Environment::GetIntermediatePath ();
	string outenv = Environment::GetOutputPath ();
	string outdir;
	string intdir;
	string vcdir;

	bool debug = ( cfg.optimization == Debug );
	bool release = ( cfg.optimization == Release );
	bool speed = ( cfg.optimization == Speed );

	bool include_idl = false;
	string include_string;

	size_t i;
	string intermediatedir = "";
	string importLib;
	// don't do the work m_configurations.size() times
	if (module.importLibrary != NULL)
	{
		intermediatedir = module.output->relative_path + vcdir;
		importLib = _strip_gcc_deffile(module.importLibrary->source->name, module.importLibrary->source->relative_path, intermediatedir);
		importLib = Path::RelativeFromDirectory (
				importLib,
				module.output->relative_path );
	}

	string module_type = GetExtension(*module.output);
	
	// Set the configuration type for this config
	ConfigurationType CfgType;
	if ( binaryType == Exe )
		CfgType = ConfigApp;
	else if ( binaryType == Lib )
		CfgType = ConfigLib;
	else if ( binaryType == Dll || binaryType == Sys )
		CfgType = ConfigDll;
	else
		CfgType = ConfigUnknown;


	if ( intenv == "obj-i386" )
		intdir = path_basedir + "obj-i386"; /* append relative dir from project dir */
	else
		intdir = intenv;

	if ( outenv == "output-i386" )
		outdir = path_basedir + "output-i386";
	else
		outdir = outenv;

	if ( configuration.UseVSVersionInPath )
	{
		vcdir = DEF_SSEP + _get_vc_dir();
	}

	fprintf ( OUT, "\t\t<Configuration\r\n" );
	fprintf ( OUT, "\t\t\tName=\"%s|Win32\"\r\n", cfg.name.c_str() );

	if ( configuration.UseConfigurationInPath )
	{
		fprintf ( OUT, "\t\t\tOutputDirectory=\"%s\\%s%s\\%s\"\r\n", outdir.c_str (), module.output->relative_path.c_str (), vcdir.c_str (), cfg.name.c_str() );
		fprintf ( OUT, "\t\t\tIntermediateDirectory=\"%s\\%s%s\\%s\"\r\n", intdir.c_str (), module.output->relative_path.c_str (), vcdir.c_str (), cfg.name.c_str() );
	}
	else
	{
		fprintf ( OUT, "\t\t\tOutputDirectory=\"%s\\%s%s\"\r\n", outdir.c_str (), module.output->relative_path.c_str (), vcdir.c_str () );
		fprintf ( OUT, "\t\t\tIntermediateDirectory=\"%s\\%s%s\"\r\n", intdir.c_str (), module.output->relative_path.c_str (), vcdir.c_str () );
	}

	fprintf ( OUT, "\t\t\tConfigurationType=\"%d\"\r\n", CfgType );
	fprintf ( OUT, "\t\t\tCharacterSet=\"2\"\r\n" );
	fprintf ( OUT, "\t\t\t>\r\n" );

	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCCLCompilerTool\"\r\n" );

	fprintf ( OUT, "\t\t\t\tOptimization=\"%d\"\r\n", release ? 2 : 0 );

	fprintf ( OUT, "\t\t\t\tAdditionalIncludeDirectories=\"" );
	bool multiple_includes = false;
	fprintf ( OUT, "./;" );
	for ( i = 0; i < includes.size(); i++ )
	{
		const std::string& include = includes[i];
		if ( strcmp ( include.c_str(), "." ) )
		{
			if ( multiple_includes )
				fprintf ( OUT, ";" );
			fprintf ( OUT, "%s", include.c_str() );
			include_string += " /I " + include;
			multiple_includes = true;
		}
	}
	if ( include_idl )
	{
		if ( multiple_includes )
			fprintf ( OUT, ";" );

		if ( configuration.UseConfigurationInPath )
		{
			fprintf ( OUT, "%s\\include\\reactos\\idl%s\\%s\r\n", intdir.c_str (), vcdir.c_str (), cfg.name.c_str() );
		}
		else
		{
			fprintf ( OUT, "%s\\include\\reactos\\idl\r\n", intdir.c_str () );
		}
	}
	if ( cfg.headers == ReactOSHeaders )
	{
		for ( i = 0; i < includes_ros.size(); i++ )
		{
			const std::string& include = includes_ros[i];
			if ( multiple_includes )
				fprintf ( OUT, ";" );
			fprintf ( OUT, "%s", include.c_str() );
			//include_string += " /I " + include;
			multiple_includes = true;
		}
	}
	else
	{
		// Add WDK or PSDK paths, if user provides them
		if (getenv ( "BASEDIR" ) != NULL &&
			(module.type == Kernel ||
			 module.type == KernelModeDLL ||
			 module.type == KernelModeDriver ||
			 module.type == KeyboardLayout))
		{
			string WdkBase, SdkPath, CrtPath, DdkPath;
			WdkBase = getenv ( "BASEDIR" );
			SdkPath = WdkBase + "\\inc\\api";
			CrtPath = WdkBase + "\\inc\\crt";
			DdkPath = WdkBase + "\\inc\\ddk";

			if ( multiple_includes )
				fprintf ( OUT, ";" );

			fprintf ( OUT, "%s;", SdkPath.c_str() );
			fprintf ( OUT, "%s;", CrtPath.c_str() );
			fprintf ( OUT, "%s", DdkPath.c_str() );
			multiple_includes = true;
		}
	}
	fprintf ( OUT, "\"\r\n" );

	StringSet defines = common_defines;

	// Always add _CRT_SECURE_NO_WARNINGS to disable warnings about not
	// using the safe functions introduced in MSVC8.
	defines.insert ( "_CRT_SECURE_NO_WARNINGS" );

	if ( debug )
	{
		defines.insert ( "_DEBUG" );
	}

	if ( cfg.headers == MSVCHeaders )
	{
		// this is a define in MinGW w32api, but not Microsoft's headers
		defines.insert ( "STDCALL=__stdcall" );
	}

	if ( binaryType == Lib || binaryType == Exe )
	{
		defines.insert ( "_LIB" );
	}
	else
	{
		defines.insert ( "_WINDOWS" );
		defines.insert ( "_USRDLL" );
	}

	fprintf ( OUT, "\t\t\t\tPreprocessorDefinitions=\"" );
	for ( StringSet::iterator it1=defines.begin(); it1!=defines.end(); it1++ )
	{
		if ( i > 0 )
			fprintf ( OUT, ";" );

		string unescaped = *it1;
		fprintf ( OUT, "%s", _replace_str(unescaped, "\"","").c_str() );
	}
	fprintf ( OUT, "\"\r\n" );
	fprintf ( OUT, "\t\t\t\tForcedIncludeFiles=\"%s\"\r\n", "warning.h");
	fprintf ( OUT, "\t\t\t\tMinimalRebuild=\"%s\"\r\n", speed ? "TRUE" : "FALSE" );
	fprintf ( OUT, "\t\t\t\tBasicRuntimeChecks=\"0\"\r\n" );
	fprintf ( OUT, "\t\t\t\tRuntimeLibrary=\"%d\"\r\n", debug ? 3 : 2 );	// 3=/MDd 2=/MD
	fprintf ( OUT, "\t\t\t\tBufferSecurityCheck=\"FALSE\"\r\n" );
	fprintf ( OUT, "\t\t\t\tEnableFunctionLevelLinking=\"FALSE\"\r\n" );

	if ( module.pch != NULL )
	{
		fprintf ( OUT, "\t\t\t\tUsePrecompiledHeader=\"2\"\r\n" );
		string pch_path = Path::RelativeFromDirectory (
			module.pch->file->name,
			module.output->relative_path );
		string::size_type pos = pch_path.find_last_of ("/");
		if ( pos != string::npos )
			pch_path.erase(0, pos+1);
		fprintf ( OUT, "\t\t\t\tPrecompiledHeaderThrough=\"%s\"\r\n", pch_path.c_str() );

		// Only include from the same module
		pos = pch_path.find("../");
		if (pos == string::npos && std::find(header_files.begin(), header_files.end(), pch_path) == header_files.end())
			header_files.push_back(pch_path);
	}
	else
	{
		fprintf ( OUT, "\t\t\t\tUsePrecompiledHeader=\"0\"\r\n" );
	}

	fprintf ( OUT, "\t\t\t\tWholeProgramOptimization=\"%s\"\r\n", release ? "FALSE" : "FALSE");
	if ( release )
	{
		fprintf ( OUT, "\t\t\t\tFavorSizeOrSpeed=\"1\"\r\n" );
		fprintf ( OUT, "\t\t\t\tStringPooling=\"true\"\r\n" );
	}

	fprintf ( OUT, "\t\t\t\tWarningLevel=\"%s\"\r\n", speed ? "0" : "3" );
	fprintf ( OUT, "\t\t\t\tDetect64BitPortabilityProblems=\"%s\"\r\n", "FALSE");
	if ( !module.cplusplus )
		fprintf ( OUT, "\t\t\t\tCompileAs=\"1\"\r\n" );

	if ( module.type == Win32CUI || module.type == Win32GUI )
	{
		fprintf ( OUT, "\t\t\t\tCallingConvention=\"%d\"\r\n", 0 );	// 0=__cdecl
	}
	else
	{
		fprintf ( OUT, "\t\t\t\tCallingConvention=\"%d\"\r\n", 2 );	// 2=__stdcall
	}

	fprintf ( OUT, "\t\t\t\tDebugInformationFormat=\"%s\"/>\r\n", speed ? "0" : release ? "3": "4");	// 3=/Zi 4=ZI

	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCCustomBuildTool\"/>\r\n" );

	if ( binaryType == Lib )
	{
		fprintf ( OUT, "\t\t\t<Tool\r\n" );
		fprintf ( OUT, "\t\t\t\tName=\"VCLibrarianTool\"\r\n" );
		fprintf ( OUT, "\t\t\t\tOutputFile=\"$(OutDir)/%s.lib\"/>\r\n", module.name.c_str() );
	}
	else
	{
		fprintf ( OUT, "\t\t\t<Tool\r\n" );
		fprintf ( OUT, "\t\t\t\tName=\"VCLinkerTool\"\r\n" );
		if (module.GetEntryPoint() == "0" && binaryType != Sys )
			fprintf ( OUT, "AdditionalOptions=\"/noentry\"" );

		if (configuration.VSProjectVersion == "9.00")
		{
			fprintf ( OUT, "\t\t\t\tRandomizedBaseAddress=\"0\"\r\n" );
			fprintf ( OUT, "\t\t\t\tDataExecutionPrevention=\"0\"\r\n" );
		}

		if (module.importLibrary != NULL)
			fprintf ( OUT, "\t\t\t\tModuleDefinitionFile=\"%s\"\r\n", importLib.c_str());

		fprintf ( OUT, "\t\t\t\tAdditionalDependencies=\"" );
		bool use_msvcrt_lib = false;
		for ( i = 0; i < libraries.size(); i++ )
		{
			if ( i > 0 )
				fprintf ( OUT, " " );
			string libpath = libraries[i].c_str();
			libpath = libpath.erase (0, libpath.find_last_of ("\\") + 1 );
			if ( libpath == "msvcrt.lib" )
			{
				use_msvcrt_lib = true;
			}
			fprintf ( OUT, "%s", libpath.c_str() );
		}
		fprintf ( OUT, "\"\r\n" );

		fprintf ( OUT, "\t\t\t\tAdditionalLibraryDirectories=\"" );

		// Add WDK libs paths, if needed
		if (getenv ( "BASEDIR" ) != NULL &&
			(module.type == Kernel ||
			 module.type == KernelModeDLL ||
			 module.type == KernelModeDriver ||
			 module.type == KeyboardLayout))
		{
			string WdkBase, CrtPath, DdkPath;
			WdkBase = getenv ( "BASEDIR" );
			CrtPath = WdkBase + "\\lib\\crt\\i386";
			DdkPath = WdkBase + "\\lib\\wnet\\i386";

			fprintf ( OUT, "%s;", CrtPath.c_str() );
			fprintf ( OUT, "%s", DdkPath.c_str() );

			if (libraries.size () > 0)
				fprintf ( OUT, ";" );
		}

		// Add conventional libraries dirs
		for (i = 0; i < libraries.size (); i++)
		{
			if ( i > 0 )
				fprintf ( OUT, ";" );

			string libpath = libraries[i].c_str();
			libpath.replace (libpath.find("---"), 3, cfg.name);
			libpath = libpath.substr (0, libpath.find_last_of ("\\") );
			fprintf ( OUT, "%s", libpath.c_str() );
		}

		fprintf ( OUT, "\"\r\n" );

		fprintf ( OUT, "\t\t\t\tOutputFile=\"$(OutDir)/%s%s\"\r\n", module.name.c_str(), module_type.c_str() );
		fprintf ( OUT, "\t\t\t\tLinkIncremental=\"%d\"\r\n", debug ? 2 : 1 );
		fprintf ( OUT, "\t\t\t\tGenerateDebugInformation=\"%s\"\r\n", speed ? "FALSE" : "TRUE" );
		fprintf ( OUT, "\t\t\t\tLinkTimeCodeGeneration=\"%d\"\r\n", release? 0 : 0);	// whole program optimization

		if ( debug )
			fprintf ( OUT, "\t\t\t\tProgramDatabaseFile=\"$(OutDir)/%s.pdb\"\r\n", module.name.c_str() );

		if ( binaryType == Sys )
		{
			if (module.GetEntryPoint() == "0")
				fprintf ( OUT, "\t\t\t\tAdditionalOptions=\" /noentry /ALIGN:0x20 /SECTION:INIT,D /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096\"\r\n" );
			else
				fprintf ( OUT, "\t\t\t\tAdditionalOptions=\" /ALIGN:0x20 /SECTION:INIT,D /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096\"\r\n" );
			fprintf ( OUT, "\t\t\t\tIgnoreAllDefaultLibraries=\"TRUE\"\r\n" );
			fprintf ( OUT, "\t\t\t\tGenerateManifest=\"FALSE\"\r\n" );
			fprintf ( OUT, "\t\t\t\tSubSystem=\"%d\"\r\n", 3 );
			fprintf ( OUT, "\t\t\t\tDriver=\"%d\"\r\n", 1 );
			fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"%s\"\r\n", module.GetEntryPoint() == "" ? "DriverEntry" : module.GetEntryPoint().c_str ());
			fprintf ( OUT, "\t\t\t\tBaseAddress=\"%s\"\r\n", baseaddr == "" ? "0x10000" : baseaddr.c_str ());
		}
		else if ( binaryType == Exe )
		{
			if ( module.type == Kernel )
			{
				fprintf ( OUT, "\t\t\t\tAdditionalOptions=\" /SECTION:INIT,D /ALIGN:0x80\"\r\n" );
				fprintf ( OUT, "\t\t\t\tIgnoreAllDefaultLibraries=\"TRUE\"\r\n" );
				fprintf ( OUT, "\t\t\t\tGenerateManifest=\"FALSE\"\r\n" );
				fprintf ( OUT, "\t\t\t\tSubSystem=\"%d\"\r\n", 3 );
				fprintf ( OUT, "\t\t\t\tDriver=\"%d\"\r\n", 1 );
				fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"KiSystemStartup\"\r\n" );
				fprintf ( OUT, "\t\t\t\tBaseAddress=\"%s\"\r\n", baseaddr.c_str ());
			}
			else if ( module.type == NativeCUI )
			{
				fprintf ( OUT, "\t\t\t\tAdditionalOptions=\" /ALIGN:0x20\"\r\n" );
				fprintf ( OUT, "\t\t\t\tSubSystem=\"%d\"\r\n", 1 );
				fprintf ( OUT, "\t\t\t\tGenerateManifest=\"FALSE\"\r\n" );
				fprintf ( OUT, "\t\t\t\tIgnoreAllDefaultLibraries=\"TRUE\"\r\n" );
				fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"NtProcessStartup\"\r\n" );
				fprintf ( OUT, "\t\t\t\tBaseAddress=\"%s\"\r\n", baseaddr.c_str ());
			}
			else if ( module.type == Win32CUI || module.type == Win32GUI || module.type == Win32SCR)
			{
				if ( use_msvcrt_lib )
				{
					fprintf ( OUT, "\t\t\t\tIgnoreAllDefaultLibraries=\"TRUE\"\r\n" );
				}
				fprintf ( OUT, "\t\t\t\tSubSystem=\"%d\"\r\n", 2 );
			}
		}
		else if ( binaryType == Dll )
		{
			if (module.GetEntryPoint() == "0")
				fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"\"\r\n" );
			else
			{
				// get rid of DllMain@12 because MSVC needs to link to _DllMainCRTStartup@12
				// when using CRT
				if (module.GetEntryPoint() == "DllMain@12")
					fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"\"\r\n" );
				else
					fprintf ( OUT, "\t\t\t\tEntryPointSymbol=\"%s\"\r\n", module.GetEntryPoint().c_str ());
			}
			fprintf ( OUT, "\t\t\t\tBaseAddress=\"%s\"\r\n", baseaddr == "" ? "0x40000" : baseaddr.c_str ());
			if ( use_msvcrt_lib )
			{
				fprintf ( OUT, "\t\t\t\tIgnoreAllDefaultLibraries=\"TRUE\"\r\n" );
			}
		}
		fprintf ( OUT, "\t\t\t\tTargetMachine=\"%d\"/>\r\n", 1 );
	}

	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCResourceCompilerTool\"\r\n" );
	fprintf ( OUT, "\t\t\t\tAdditionalIncludeDirectories=\"" );
	multiple_includes = false;
	fprintf ( OUT, "./;" );
	for ( i = 0; i < includes.size(); i++ )
	{
		const std::string& include = includes[i];
		if ( strcmp ( include.c_str(), "." ) )
		{
			if ( multiple_includes )
				fprintf ( OUT, ";" );
			fprintf ( OUT, "%s", include.c_str() );
			multiple_includes = true;
		}
	}
	if ( cfg.headers == ReactOSHeaders )
	{
		for ( i = 0; i < includes_ros.size(); i++ )
		{
			const std::string& include = includes_ros[i];
			if ( multiple_includes )
				fprintf ( OUT, ";" );
			fprintf ( OUT, "%s", include.c_str() );
			multiple_includes = true;
		}
	}
	fprintf ( OUT, "\"/>\r\n " );

	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCMIDLTool\"/>\r\n" );
	if (configuration.VSProjectVersion == "8.00")
	{
		fprintf ( OUT, "\t\t\t<Tool\r\n" );
		fprintf ( OUT, "\t\t\t\tName=\"VCManifestTool\"\r\n" );
		fprintf ( OUT, "\t\t\t\tEmbedManifest=\"false\"/>\r\n" );
	}
	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCPostBuildEventTool\"/>\r\n" );
	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCPreBuildEventTool\"/>\r\n" );
	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCPreLinkEventTool\"/>\r\n" );
	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCWebServiceProxyGeneratorTool\"/>\r\n" );
	fprintf ( OUT, "\t\t\t<Tool\r\n" );
	fprintf ( OUT, "\t\t\t\tName=\"VCWebDeploymentTool\"/>\r\n" );
	fprintf ( OUT, "\t\t</Configuration>\r\n" );
}


void
VCProjMaker::_generate_makefile_configuration( const Module& module, const MSVCConfiguration& cfg )
{
	string path_basedir = module.GetPathToBaseDir ();
	string intenv = Environment::GetIntermediatePath ();
	string outenv = Environment::GetOutputPath ();

	string outdir;
	string intdir;
	string vcdir;


	if ( intenv == "obj-i386" )
		intdir = path_basedir + "obj-i386"; /* append relative dir from project dir */
	else
		intdir = intenv;

	if ( outenv == "output-i386" )
		outdir = path_basedir + "output-i386";
	else
		outdir = outenv;

	if ( configuration.UseVSVersionInPath )
	{
		vcdir = DEF_SSEP + _get_vc_dir();
	}

	fprintf ( OUT, "\t\t<Configuration\r\n" );
	fprintf ( OUT, "\t\t\tName=\"%s|Win32\"\r\n", cfg.name.c_str() );

	if ( configuration.UseConfigurationInPath )
	{
		fprintf ( OUT, "\t\t\tOutputDirectory=\"%s\\%s\\%s\"\r\n", outdir.c_str (), module.output->relative_path.c_str (), cfg.name.c_str() );
		fprintf ( OUT, "\t\t\tIntermediateDirectory=\"%s\\%s\\%s\"\r\n", intdir.c_str (), module.output->relative_path.c_str (), cfg.name.c_str() );
	}
	else
	{
		fprintf ( OUT, "\t\t\tOutputDirectory=\"%s\\%s\"\r\n", outdir.c_str (), module.output->relative_path.c_str () );
		fprintf ( OUT, "\t\t\tIntermediateDirectory=\"%s\\%s\"\r\n", intdir.c_str (), module.output->relative_path.c_str () );
	}

	fprintf ( OUT, "\t\t\tConfigurationType=\"0\"\r\n");
	fprintf ( OUT, "\t\t\t>\r\n" );

	fprintf ( OUT, "\t\t\t<Tool\r\n" );

	fprintf ( OUT, "\t\t\t\tName=\"VCNMakeTool\"\r\n" );
	fprintf ( OUT, "\t\t\t\tBuildCommandLine=\"%srosbuild.bat build %s\"\r\n", path_basedir.c_str (), module.name.c_str ());
	fprintf ( OUT, "\t\t\t\tReBuildCommandLine=\"%srosbuild.bat rebuild %s\"\r\n", path_basedir.c_str (), module.name.c_str ());
	fprintf ( OUT, "\t\t\t\tCleanCommandLine=\"%srosbuild.bat clean %s\"\r\n", path_basedir.c_str (), module.name.c_str ());
	fprintf ( OUT, "\t\t\t\tOutput=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tPreprocessorDefinitions=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tIncludeSearchPath=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tForcedIncludes=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tAssemblySearchPath=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tForcedUsingAssemblies=\"\"\r\n");
	fprintf ( OUT, "\t\t\t\tCompileAsManaged=\"\"\r\n");

	fprintf ( OUT, "\t\t\t/>\r\n" );
	fprintf ( OUT, "\t\t</Configuration>\r\n" );
}
