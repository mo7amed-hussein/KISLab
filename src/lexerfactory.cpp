/***************************************************************************
 *   Copyright (C) 2017 by Mohamed Hussein                                 *
 *   m.hussein1389@gmail.com                                               *
     https://github.com/mo7amed-hussein/                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/
#include "lexerfactory.h"
#include"config.h"
#include<QFileInfo>
LexerFactory::LexerFactory()
{

}

 QsciLexer* LexerFactory::getLexer(QString lex)
 {
    if(QString::compare(lex,CPP,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerCPP();
    }
    else if(QString::compare(lex,BATCH,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerBatch();
    }
    else if(QString::compare(lex,CSHarP,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerCSharp;
    }
    else if(QString::compare(lex,CSS,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerCSS;
    }
    else if(QString::compare(lex,CMAKE,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerCMake;
    }
    else if(QString::compare(lex,COFFEESCRIPT,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerCoffeeScript;
    }
    else if(QString::compare(lex,D,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerD;
    }
    else if(QString::compare(lex,DIFF,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerDiff;
    }
    else if(QString::compare(lex,FORTRAN,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerFortran;
    }
    else if(QString::compare(lex,FORTRAN77,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerFortran77;
    }
    else if(QString::compare(lex,HTML,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerHTML;
    }
    else if(QString::compare(lex,JAVA,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerJava;
    }
    else if(QString::compare(lex,JAVASCRIPT,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerJavaScript;
    }
    else if(QString::compare(lex,LUA,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerLua;
    }
    else if(QString::compare(lex,MAKEFILE,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerMakefile;
    }
    else if(QString::compare(lex,MATLAB,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerMatlab;
    }
    else if(QString::compare(lex,PASCAL,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerPascal;
    }
    else if(QString::compare(lex,PERL,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerPerl;
    }
    else if(QString::compare(lex,POSTSCRIPT,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerPostScript;
    }
    else if(QString::compare(lex,PROPERTIES,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerProperties;
    }
    else if(QString::compare(lex,PYTHON,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerPython;
    }
    else if(QString::compare(lex,RUBY,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerRuby;
    }
    else if(QString::compare(lex,SQL,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerSQL;
    }
    else if(QString::compare(lex,TCL,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerTCL;
    }
    else if(QString::compare(lex,TEX,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerTeX;
    }
    else if(QString::compare(lex,VERILOG,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerVerilog;
    }
    else if(QString::compare(lex,VHDL,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerVHDL;
    }
    else if(QString::compare(lex,XML,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerXML;
    }
    else if(QString::compare(lex,YAML,Qt::CaseInsensitive)==0)
    {
        return new QsciLexerYAML;
    }
    else
    {
        return NULL;
    }




 }
QString LexerFactory::getFileType(QString &filename)
{
    QFileInfo f(filename);
    QString fileExt=f.completeSuffix();
    if(fileExt=="bat" || fileExt=="cmd" || fileExt=="nt")
    {
     return BATCH;
    }
    else if (fileExt=="c" || fileExt=="cpp" || fileExt=="cc" || fileExt=="cxx" || fileExt=="h" || fileExt=="hpp" || fileExt=="hxx")
    {
        return CPP;
    }
    else if ( fileExt=="cs")
    {
        return CSHarP;
    }
    else if (fileExt=="cmake")
    {
        return CMAKE;
    }

     else if ( fileExt=="litcoffee")
    {
        return COFFEESCRIPT;
    }
     else if ( fileExt=="css" )
    {
        return CSS;
    }
     else if (fileExt=="d")
    {
        return D;
    }
     else if ( fileExt=="diff" || fileExt=="patch")
    {
        return DIFF;
    }
     else if (fileExt=="f" || fileExt=="for" || fileExt=="f90" || fileExt=="f95" || fileExt=="f2k")
    {
        return FORTRAN;
    }
    else if (fileExt=="f77")
    {
        return FORTRAN77;
    }
     else if (fileExt=="htm" || fileExt=="html" || fileExt=="shtm" || fileExt=="shtml" || fileExt=="xhtml" || fileExt=="hta")
    {
        return HTML;
    }
    else if (fileExt=="java")
    {
        return JAVA;
    }
    else if (fileExt=="js")
    {
        return JAVASCRIPT;
    }
    else if (fileExt=="lua")
    {
        return LUA;
    }
     else if (fileExt=="mak")
    {
        return MAKEFILE;
    }
     else if ( fileExt=="m")
    {
        return MATLAB;
    }
     else if (fileExt=="pas" || fileExt=="inc")
    {
        return PASCAL;
    }
     else if (fileExt=="pl" || fileExt=="pm" || fileExt=="plx")
    {
        return PERL;
    }
     else if (fileExt=="ps")
    {
        return POSTSCRIPT;
    }
     else if (fileExt=="properties")
    {
        return PROPERTIES;
    }
     else if (fileExt=="py" || fileExt=="pyw")
    {
        return PYTHON;
    }
     else if ( fileExt=="rb" || fileExt=="rbw")
    {
        return RUBY;
    }
     else if (fileExt=="sql")
    {
        return SQL;
    }
     else if (fileExt=="tcl")
    {
        return TCL;
    }
     else if (fileExt=="tex")
    {
        return TEX;
    }
     else if (fileExt=="vhd" || fileExt=="vhdl")
    {
        return VHDL;
    }
     else if ( fileExt=="v" || fileExt=="sv" || fileExt=="vh" || fileExt=="svh")
    {
        return VERILOG;
    }
    else if ( fileExt=="xml" || fileExt=="xsml" || fileExt=="xsl" || fileExt=="kml" || fileExt=="wsdl" || fileExt=="xlf"|| fileExt=="xliff")
    {
        return XML;
    }
    else if ( fileExt=="yml")
    {
        return YAML;
    }
    else
    {
        return "just";
    }


}
