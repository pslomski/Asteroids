//////////////////////////////////////////////////////////////////////
// SplitPath.h : interface for the CSplitPath class.                //
// (c) 1999, Kevin Lussier                                          //
//////////////////////////////////////////////////////////////////////

#ifndef __SPLITPATH_H__
#define __SPLITPATH_H__

#pragma once


#include <string>

class CSplitPath
{ 
	// Construction
public: 
    CSplitPath( LPCTSTR lpszPath = NULL );
	
	// Operations
    BOOL    Split(LPCTSTR lpszPath );
	std::string GetPath( void ) { return path_buffer; }
    std::string GetDrive( void ) { return drive; }
    std::string GetDirectory( void ) { return dir; }
    std::string GetFileName( void ) { return fname; }
    std::string GetExtension( void ) { return ext; }
	
	// Attributes
protected:
    TCHAR path_buffer[_MAX_PATH];
    TCHAR drive[_MAX_DRIVE];
    TCHAR dir[_MAX_DIR];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
}; 

#endif  // __SPLITPATH_H__

