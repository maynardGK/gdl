/* *************************************************************************
                          gdlgstream.cpp  -  graphic stream
                             -------------------
    begin                : July 22 2002
    copyright            : (C) 2002 by Marc Schellens
    email                : m_schellens@users.sf.net
 ***************************************************************************/

/* *************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// try because of segfault in magick
// #include "gdlgstream.hpp"

#include "includefirst.hpp"

#include <iostream>

#include "graphics.hpp"
#include "gdlgstream.hpp"
#include "initsysvar.hpp"

using namespace std;

// bool GDLGStream::plstreamInitCalled = false;

// void PLPlotAbortHandler(const char *c)
// {
//   cout << "PLPlot abort handler: " << c << endl;
// }
// 
// int PLPlotExitHandler(const char *c)
// {
//   cout << "PLPlot exit handler: " << c << endl;
//   return 0;
// }
// 
// void GDLGStream::SetErrorHandlers()
// {
//   plsexit( PLPlotExitHandler);
//   plsabort( PLPlotAbortHandler);
// }

void GDLGStream::Color( ULong c, DLong decomposed, UInt ix)
{
  DByte r,g,b;
  if (decomposed == 0) c = c & 0x0000FF;

  if( c < ctSize && decomposed == 0)
    {
      Graphics::GetCT()->Get( c, r, g, b);
    }
  else
    {
      r = c & 0xFF;
      g = (c >> 8)  & 0xFF;
      b = (c >> 16) & 0xFF;
    }
  plstream::scol0( ix, r, g, b);
  plstream::col0( ix);
}

void GDLGStream::Background( ULong c, DLong decomposed)
{
  DByte r,g,b;
  if (decomposed == 0) c = c & 0x0000FF;

  if( c < ctSize && decomposed == 0)
    {
      Graphics::GetCT()->Get( c, r, g, b);
    }
  else
    {
      r = c & 0xFF;
      g = (c >> 8)  & 0xFF;
      b = (c >> 16) & 0xFF;
    }
  /*
  DByte r,g,b;
  if( c < ctSize)
    {
      Graphics::GetCT()->Get( c, r, g, b);
    }
  else
    {
      r = c & 0xFF;
      g = (c >> 8)  & 0xFF;
      b = (c >> 16) & 0xFF;
    }
  */
  plstream::scolbg( r, g, b);
}

void GDLGStream::DefaultCharSize()
{
  DString name = (*static_cast<DStringGDL*>(
    SysVar::D()->GetTag(SysVar::D()->Desc()->TagIndex("NAME"), 0)
  ))[0];

  if (name == "X") plstream::schr( 1.5, 1.0);
  else if (name == "PS") plstream::schr( 3.5, 1.0);
  else plstream::schr( 0, 1.0);
}

void GDLGStream::NextPlot( bool erase)
{
  DLongGDL* pMulti = SysVar::GetPMulti();

  DLong nx = (*pMulti)[ 1];
  DLong ny = (*pMulti)[ 2];
  DLong nz = (*pMulti)[ 3];

  DLong dir = (*pMulti)[ 4];

  nx = (nx>0)?nx:1;
  ny = (ny>0)?ny:1;
  nz = (nz>0)?nz:1;

  plstream::ssub( nx, ny); // changes charsize

  if( (*pMulti)[ 0] <= 0 || (*pMulti)[ 0] == nx*ny)
    //  if( (*pMulti)[ 0] <= 0)
    {
      if( erase)
	{
	  eop();           // overridden (for Z-buffer)  
	  plstream::bop(); // changes charsize
	}

      plstream::adv(1);
      (*pMulti)[ 0] = nx*ny*nz-1;
    }
  else
    {
      DLong pMod = (*pMulti)[ 0] % (nx*ny);
      if( dir == 0)
      {
	plstream::adv(nx*ny - pMod + 1);
      }
      else
	{
	  int p = nx*ny - pMod;
	  int pp = p*nx % (nx*ny) + p/ny + 1;
	  plstream::adv(pp);
	}

      if( erase) 
      {
        --(*pMulti)[ 0];
      }
    }

  // restore charsize
  DefaultCharSize();
}

void GDLGStream::NoSub()
{
  plstream::ssub( 1, 1); // changes charsize
  plstream::adv( 0);
  DefaultCharSize();
}

// default is a wrapper for gpage()
void GDLGStream::GetGeometry( long& xSize, long& ySize, long& xoff, long& yoff)
{
  
  PLFLT xp; PLFLT yp; 
  PLINT xleng; PLINT yleng;
  PLINT plxoff; PLINT plyoff;
  gpage( xp, yp, xleng, yleng, plxoff, plyoff);
  
  xSize = xleng;
  ySize = yleng;
  xoff = plxoff;
  yoff = plyoff;
}

// SA: embedded font attributes handling (IDL to plPlot syntax translation)
const char * GDLGStream::TranslateFormatCodes(const char *in) 
{
  bool debug = false;
  static char errmsg[] = "Invalid graphtext command: ...!  ";
  static const size_t errmsglen = strlen(errmsg);

  // TODO: 
  // - in IDL the D.FLAGS bit value ((!D.FLAGS AND 4096) EQ 0)
  //   is designed to indicate if the device does not support extended commands
  // - unicode substitution for non-unicode terminals results in plplot controll
  //   sequences being printed 
  // - ... a look-up table instead of the long switch/case blocks ...
 
  size_t len = strlen(in);

  // skip conversion if the string is empty
  if (len == 0) return in;

  const string fonts[] = {
    "#fn",      // !0  : unused
    "#fn",      // !1  : unused
    "#fn",      // !2  : unused
    "#fn",      // !3  : simplex Roman (default)
    "#fn",      // !4  : simplex Greek
    "#fn",      // !5  : duplex Roman
    "#fr",      // !6  : complex Roman
    "#fr",      // !7  : complex Greek
    "#fi",      // !8  : complex italic 
    "#fn",      // !9  : math/special characters
    "#fn",      // !10 : special characters
    "#fn",      // !11 : Gothic English 
    "#fs",      // !12 : simplex script
    "#fs",      // !13 : complex script
    "#fn",      // !14 : Gothic Italian
    "#fn",      // !15 : Gothic German
    "#fn",      // !16 : Cyrillic
    "#fr",      // !17 : triplex Roman
    "#fi",      // !18 : triplex Italic
    "#fn",      // !19 : 
    "#fn",      // !20 : miscellaneous
    "#fn",      // !21 :
    "#fn",      // !22 :
    "#fn",      // !23 :
    "#fn",      // !24 :
    "#fn",      // !25 :
    "#fn",      // !26 :
    "#fn",      // !27 :
    "#fn",      // !28 :
    "#fn",      // !29 :
  };

  const int default_fnt = 3;
  int curr_fnt = default_fnt; // (current font number from the above table)
  int next_fnt = default_fnt; // (next letter font - same as curr_fnt save for the case of !G, !W and !M commands)
  int curr_lev = 0; // (incremented with #u, decremented with #d)
  int curr_pos = 0; // (current position in string)
  int save_pos = 0; // (position in string used in !S/!R save/restore)
  string out = string("");

  for (size_t i = 0; i < len; i++) {
    if (in[i] == '!' && in[i + 1] != '!')
    {
      size_t j = 1; // number of characters analysed (after !)
      switch (in[i + 1])
      {
        case '1' : // 2-char codes begining with !1
        {
          switch (in[i + 2])
          {
            case '0' : // !10 : Special characters
            case '1' : // !11 : Gothic English
            case '2' : // !12 : Simplex Script
            case '3' : // !13 : Complex Script
            case '4' : // !14 : Gothic Italian
            case '5' : // !15 : Gothic German
            case '6' : // !16 : Cyrillic
            case '7' : // !17 : Triplex Roman
            case '8' : // !18 : Triplex Italic
            case '9' : // !19 : 
              j++; 
              out += fonts[curr_fnt = next_fnt = 10 - 48 + in[i + 2]]; 
              break;
            default : // illegal command / end of string
              errmsg[errmsglen - 2] = in[i + 1];
              errmsg[errmsglen - 1] = in[i + 2];
              j++;
              Warning(errmsg);
          }
          break;
        }
        case '2' : // 2-char codes begining with !2
        {
          switch (in[i + 2])
          {
            case '0' : // !20 : Miscellaneous
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' :
              j++;
              out += fonts[curr_fnt = next_fnt = 20 - 48 + in[i + 2]];
              break;
            default : // illegal command / end of string
              errmsg[errmsglen - 2] = in[i + 1];
              errmsg[errmsglen - 1] = in[i + 2];
              j++;
              Warning(errmsg);
          }
          break;
        }

        case '3' : // simplex roman
        case '4' : // greek script
        case '5' : // duplex roman
        case '6' : // complex roman
        case '7' : // complex greek
        case '8' : // complex italic
        case '9' : // Math/special characters
          out += fonts[next_fnt = curr_fnt = in[i + 1] - 48];
          break;

        case 'M' : case 'm' : // one Math/special character
          curr_fnt = 9;
          break;
        case 'G' : case 'g' : // one Gothic English character
          curr_fnt = 11;
          break;
        case 'W' : case 'w' : // one Simplex Script character
          curr_fnt = 12; 
          break;

        case 'C' : case 'c' : // carriage return
          out += "#[0xD]";
          break;

        case 'X' : case 'x' : // reversion to entry font 
          out += fonts[curr_fnt = next_fnt = default_fnt];
          break;

        case 'S' : case 's' : // save position
          save_pos = curr_pos;
          break;

        case 'L' : case 'l' : // 2nd level subscript
          curr_lev--;
          out += "#d";
          // continues!
        case 'D' : case 'd' : // subscript
        case 'I' : case 'i' : // index
          curr_lev--;
          out += "#d";
          break;
        case 'R' : case 'r' : // restore position
          for (; save_pos < curr_pos; curr_pos--) out += "#b";
          // continues!
        case 'A' : case 'a' : // shift above the division line
          //TODO: plplot seems not to support it 
        case 'B' : case 'b' : // shift below the division line
          //TODO: plplot seems not to support it
        case 'N' : case 'n' : // back to normal size
          while (curr_lev != 0) 
          {
            if (curr_lev > 0) out += "#d", curr_lev--;
            else out += "#u", curr_lev++;
          }
          // assumed from examples in documentation
          if (in[i + 1] == 'N' || in[i + 1] == 'n') out += fonts[curr_fnt = next_fnt = default_fnt];
          break;
        case 'U' : case 'u' : // superscript
        case 'E' : case 'e' : // exponent
          curr_lev++;
          out += "#u";
          break;
        case 'Z' : case 'z' : // unicode chars via "#[nnn]"
          // first, the only two examples from IDL doc:
          // - !Z(00B0) - degree symbol
          // - !Z(U+0F1) - Spanish "n" with tilde (as in El ni\~no)
          // searching for the left parenthesis
          if (in[i + 2] != '(') 
          {
            if (in[i + 2] == '!' && in[i + 3] == 'Z') break; // !Z!Z is valid
            if (in[i + 2] == '\0') break; // end of string after !Z is valid
            Warning("Error using Hershey characters: Parentheses required for !Z.");
            goto retrn;
          } 
          else 
          {
            // searching for the right parenthesis
            size_t right_par = i + 2;
            while (in[++right_par] != ')') if (right_par == len) 
            {
              Warning("Error using Hershey characters: Parentheses required for !Z.");
              goto retrn;
            }
            size_t chars = 0;
            while (j + i + 1 != right_par)
            {
              // tokenizing (plethora of other tokens is accepted by IDL!)
              while (++j + i + 1 != right_par && in[j + i + 1] != ',') chars++;
              if (in[j + i + 1 - chars] == 'U' && in[j + i + 2 - chars] == '+') chars-=2; // U+NNNN syntax
              if (chars > 4) 
              {
                Warning("Error using Hershey characters: !Z hexadecimal value too large.");
                goto retrn;
              }
              else if (chars > 0)
              {
                out += "#[0x";
                for (; chars > 0; chars--) out += in[j + i + 1 - chars];          
                out += "]";
                curr_pos++;
              }
            }
            j++; // right parenthesis
          }
          break;
        case '\0' : // end of string
        default : // unknown command
          j--;
          curr_pos++;
          out += "!";
          break;
      }
      i += j; 
    }
    else 
    {
      curr_pos++;
      // handling IDL exclamation mark escape '!!'
      if (in[i] == '!') i++;
      // handling plplot number sign escape '##'
      if 
      (
        curr_fnt !=  9 && 
        curr_fnt != 10 && 
        curr_fnt != 16 && 
        curr_fnt != 20 && 
        in[i] == '#'
      ) out += "##"; 
      else switch (curr_fnt)
      {
        case 9 : // math symbols
          switch (in[i])
          {
            case '!' : out += "#(2229)"; break; // vertical line
            case '%' : out += "#(218)";  break; // degree circle
            case 'X' : out += "#(227)";  break; // x (cross) sign
            case 'D' :                          // as below
            case 'd' : out += "#(2265)"; break; // partial deriv sign
            case 'r' : out += "#(2267)"; break; // square root sign bigger
            case 'R' : out += "#(2411)"; break; // square root sign biggest
            case 'S' : out += "#(2267)"; break; // square root sign 
            case 'I' : out += "#(2412)"; break; // big integral sign
            case 'i' : out += "#(2268)"; break; // small integral sign
            case '/' : out += "#(2237)"; break; // range (dot dash dot) sign
            case '=' : out += "#(2239)"; break; // non equal sign
            case '6' : out += "#(2261)"; break; // arrow right
            case '7' : out += "#(2262)"; break; // arrow up
            case '4' : out += "#(2263)"; break; // arrow left
            case '5' : out += "#(2264)"; break; // arrow down
            case 'f' : out += "#(2283)"; break; // female sex sign
            case 'm' : out += "#(2285)"; break; // male sex sign
            case '<' : out += "#(2407)"; break; // big curly brace left
            case '>' : out += "#(2408)"; break; // big curly brace right
            case '#' : out += "#(737)";  break; // two vertical lines
            case '$' : out += "#(766)";  break; // infty
            case '&' : out += "#(2276)"; break; // paragraph
            case 'P' : out += "#(2147)"; break; // phi
            case 'p' : 
              out += "#fsp"; 
              out += fonts[curr_fnt];    break; // p script
            case 'q' : 
              out += "#fsq"; 
              out += fonts[curr_fnt];    break; // q script
            case ':' : out += "#(2240)"; break; // equal by definition sign
            case '.' : out += "#(850)";  break; // filled dot
            case 'B' : out += "#(841)";  break; // empty square
            case 'F' : 
              out += "#fsF"; 
              out += fonts[curr_fnt];    break; // F script
            case 'J' : out += "#(2269)"; break; // closed path integral
            case 'O' : out += "#(2277)"; break; // 'upper' cross sign
            case 'o' : out += "#(2278)"; break; // double cross sign
            case 'j' : 
              out += "#fsj"; 
              out += fonts[curr_fnt];    break; // j italic
            case 's' : out += "#(687)";  break; // some greek zig-zag 
            case 't' : 
              out += "#fs#(634)";        break; // theta-like greek zig-zag 
            case 'A' : out += "#(2246)"; break; // similar / tilde
            case 'T' : out += "#(740)";  break; // three dots
            case 'U' : out += "#(741)";  break; // spades (card sign)
            case 'V' : out += "#(743)";  break; // diamonds (card sign)
            case 'W' : out += "#(745)";  break; // clover sign
            case 'u' : out += "#(742)";  break; // hearts (card sign)
            case 'v' : out += "#(744)";  break; // clubs (card sign)
            case 'w' : out += "#(746)";  break; // ?
            case '_' :                          // as below 
            case 127u : out += "#(830)"; break; // '---' sign
            case 'H' : out += "#(908)";  break; // ?
            case '@' : out += "#(2077)"; break; // ? kappa like
            case 'n' : out += "#(2281)"; break; // circle with dot inside
            case 'e' : out += "#(2260)"; break; // mirrored E
            case 'E' : out += "#(2279)"; break; // element of
            case 'G' : out += "#(2266)"; break; // nabla
            case 'l' : out += "#(2243)"; break; // less or equal
            case 'b' : out += "#(2244)"; break; // grater or equal
            case '?' : out += "#(2245)"; break; // proportional
            case '^' :                          // as below
            case '~' : out += "#(2247)"; break; // ^
            case '+' : out += "#(2233)"; break; // plus minus
            case '-' : out += "#(2234)"; break; // minus plus
            case '(' : out += "#(2403)"; break; // big bracket left
            case ')' : out += "#(2404)"; break; // big bracket right
            case '[' :                          // as below
            case '{' : out += "#(2405)"; break; // big rect. brace left
            case ']' :                          // as below
            case '}' : out += "#(2406)"; break; // big rect. brace right
            case 'h' : out += "#(909)";  break; // ? police badge-like
            case 'x' : out += "#(738)";  break; // perpendicular sign
            case 'a' : out += "#(739)";  break; // angle
            case 'c' : out += "#(823)";  break; // ?
            case '0' : out += "#(2256)"; break; // set theory C-like 
            case '1' : out += "#(2257)"; break; // set theory U-like
            case '2' : out += "#(2258)"; break; // set theory )-like
            case '3' : out += "#(2259)"; break; // set theory ^-like
            case 'N' : out += "#(2311)"; break; // double wave
            case '`' : out += "'";       break; // ` -> '
            // empty chars:
            case '8' : case '9' : case ';' : case 'K' : case 'L' : case 'M' : case 'Q' :
            case 'Y' : case 'Z' : case '\\' : case 'k' : case 'y' : case 'z' : case '|' :
            case 'g' : 
            // unsupported chars:
            case 'C' : // tick sign
              out += " "; break;
              break;
            default : 
              out.append(in, i, 1);
              break;
          }
          break;
        case 20 : // misc symbols
          switch (in[i])
          {
            case 'b' : out += "#(851)";  break;  // filled square
            case ':' :                           // small filled triangle up
            case 'C' : out += "#(852)";  break;  // filled triangle up
            case 'D' : out += "#(854)";  break;  // filled triangle down
            case '/' : out += "#(2323)"; break;  // musical sharp sign
            case 'M' : out += "#(874)";  break;  // ?
            case 'K' : out += "#(870)";  break;  // palm sign
            case '^' :                           // as below
            case '~' : out += "#(834)";  break;  // upside down triangle
            case 'N' : out += "#(900)";  break;  // circle smallest
            case 'n' : out += "#(901)";  break;  // circle smaller
            case 'O' : out += "#(902)";  break;  // circle small
            case 'o' : out += "#(903)";  break;  // circle 
            case 'P' : out += "#(904)";  break;  // circle 
            case 'p' : out += "#(905)";  break;  // circle big
            case 'Q' : out += "#(906)";  break;  // circle bigger
            case 'q' : out += "#(907)";  break;  // circle biggest
            case '?' : out += "#(767)";  break;  // flash
            case '<' : out += "#(768)";  break;  // paragraph-like
            case 'A' : out += "#(754)";  break;  // upper semicircle filled
            case 'G' : out += "#(862)";  break;  // two hammers
            case 'E' : out += "#(856)";  break;  // star
            case 'e' : out += "#(857)";  break;  // flag
            case 'f' : out += "#(861)";  break;  // ?
            case 'g' : out += "#(863)";  break;  // tower / look-out
            case 'h' : out += "#(865)";  break;  // grave
            case 'L' : out += "#(872)";  break;  // deciduous tree
            case 'k' : out += "#(871)";  break;  // coniferous tree
            case '"' : out += "#(2409)"; break;  // big inverted-s-like shape
            case '$' : out += "#(2376)"; break;  // ?
            case '%' : out += "#(2382)"; break;  // ?
            case '`' : 
            case '\'' : out += "#(766)"; break;  // infty
            case '(' : out += "#(2374)"; break;  // natural (music)
            case ')' : out += "#(2375)"; break;  // flat (music)
            case '*' : out += "#(2372)"; break;  // ? minim (music)
            case '-' :                           // as below
            case '+' : out += "#(2371)"; break;  // ? 2xminim length note (music)
            case ',' : out += "#(2329)"; break;  // ? rest (music)
            case '.' : out += "#(2380)"; break;  // treble clef
            case '0' : out += "#(2306)"; break;  // ? Gothic-like m
            case '1' : out += "#(2307)"; break;  // ? underlined omega
            case '2' : out += "#(2308)"; break;  // ? Gothic-like m
            case '3' : out += "#(2309)"; break;  // NE double arrow
            case '4' : out += "#(2310)"; break;  // ?
            case '5' : out += "#(2311)"; break;  // ?
            case '6' : out += "#(2312)"; break;  // ?
            case '7' : out += "#(2317)"; break;  // ?
            case '8' : out += "#(2318)"; break;  // ?
            case '9' : out += "#(2319)"; break;  // ?
            case '=' : out += "#(2377)"; break;  // ?
            case '>' : out += "#(831)";  break;  // ?
            case 'V' : out += "#(2291)"; break;  // crescent
            case 'W' : out += "#(2293)"; break;  // 8-arm star
            case 'X' : out += "#(2295)"; break;  // ?
            case 'Y' : out += "#(2302)"; break;  // ?
            case 'Z' : out += "#(2304)"; break;  // 69 ;)
            case 'r' : out += "#(2282)"; break;  // ? female sex sign like
            case 'u' : out += "#(2290)"; break;  // ? P-like
            case 'v' : out += "#(2292)"; break;  // ?
            case 'w' : out += "#(2294)"; break;  // ? omega-like
            case 'x' : out += "#(2301)"; break;  // ? fountain-like
            case 'y' : out += "#(2303)"; break;  // ?
            case '[' :                           // as below
            case '{' : out += "#(2332)"; break;  // ? ladder-like
            case ']' :                           // as below
            case '}' : out += "#(2381)"; break;  // bass clef
            case '_' :                           // as below
            case 127 : out += "#(2410)"; break;  // big s-like shape
            case '!' : out += "#(764)";  break;  // S-like
            case '&' : out += "#(765)";  break;  // tilde-like half-infty sign
            case 'B' : out += "#(850)";  break;  // filled dot
            case 'F' : out += "#(860)";  break;  // anchor
            case 'I' : out += "#(866)";  break;  // cross
            case 'J' : out += "#(868)";  break;  // Jewish star
            case 'R' : out += "#(735)";  break;  // square-like
            case 'a' : out += "#(755)";  break;  // filled triangle 
            case 'i' : out += "#(867)";  break;  // small screscent
            case 'j' : out += "#(869)";  break;  // bell
            case ' ' : out += "#(2328)"; break; // ?
            case '#' : out += "#(2331)"; break; // ?
            case 'S' : out += "#(2284)"; break; // empty circel with plus sign inside
            case 'T' : out += "#(2287)"; break; // ?
            case 'U' : out += "#(2289)"; break; // ? greep psi-like
            case '\\' :  // as below
            case '|' : out += "#(833)";  break; // ? electrical ground sign-like
            case 'c' : out += "#(853)";  break; // filled triangle left
            case 'd' : out += "#(855)";  break; // filled triangle right
            case '@' : out += "#(832)";  break; // ^
            case 'H' : out += "#(864)";  break; // flower in a flowerpot
            case 's' : out += "#(2286)"; break; // 4-like
            case 't' : out += "#(2288)"; break; // ?
            case ';' : out += "#(840)";  break; // empty circle
            case 'l' : out += "#(873)";  break; // ?
            case 'z' : out += "#(2305)"; break; // ?
            case 'm' : out += "#(899)";  break; // smallest circle - dot
            default : 
              out.append(in, i, 1);
              break;
          }
          break;
        case 16 : // Cyrillic
          switch (in[i])
          { //         uppercase                           lowercase
            case 'A' : out += "#(2801)"; break; case 'a' : out += "#(2901)"; break; // [a]
            case 'B' : out += "#(2802)"; break; case 'b' : out += "#(2902)"; break; // [b]
            case 'C' : out += "#(2803)"; break; case 'c' : out += "#(2903)"; break; // [v]
            case 'D' : out += "#(2804)"; break; case 'd' : out += "#(2904)"; break; // [g]
            case 'E' : out += "#(2805)"; break; case 'e' : out += "#(2905)"; break; // [d]
            case 'F' : out += "#(2806)"; break; case 'f' : out += "#(2906)"; break; // [ye]
            case 'G' : out += "#(2807)"; break; case 'g' : out += "#(2907)"; break; // [zsh]
            case 'H' : out += "#(2808)"; break; case 'h' : out += "#(2908)"; break; // [z]
            case 'I' : out += "#(2809)"; break; case 'i' : out += "#(2909)"; break; // [i/e]
            case 'J' : out += "#(2810)"; break; case 'j' : out += "#(2910)"; break; // [ii]
            case 'K' : out += "#(2811)"; break; case 'k' : out += "#(2911)"; break; // [k]
            case 'L' : out += "#(2812)"; break; case 'l' : out += "#(2912)"; break; // [l]
            case 'M' : out += "#(2813)"; break; case 'm' : out += "#(2913)"; break; // [m]
            case 'N' : out += "#(2814)"; break; case 'n' : out += "#(2914)"; break; // [n]
            case 'O' : out += "#(2815)"; break; case 'o' : out += "#(2915)"; break; // [o]
            case 'P' : out += "#(2816)"; break; case 'p' : out += "#(2916)"; break; // [p]
            case 'Q' : out += "#(2817)"; break; case 'q' : out += "#(2917)"; break; // [r]
            case 'R' : out += "#(2818)"; break; case 'r' : out += "#(2918)"; break; // [s]
            case 'S' : out += "#(2819)"; break; case 's' : out += "#(2919)"; break; // [t]
            case 'T' : out += "#(2820)"; break; case 't' : out += "#(2920)"; break; // [u/woo]
            case 'U' : out += "#(2821)"; break; case 'u' : out += "#(2921)"; break; // [f]
            case 'V' : out += "#(2822)"; break; case 'v' : out += "#(2922)"; break; // [h]
            case 'W' : out += "#(2823)"; break; case 'w' : out += "#(2923)"; break; // [c]
            case 'X' : out += "#(2824)"; break; case 'x' : out += "#(2924)"; break; // [ch]
            case 'Y' : out += "#(2825)"; break; case 'y' : out += "#(2925)"; break; // [sh]
            case 'Z' : out += "#(2826)"; break; case 'z' : out += "#(2926)"; break; // [shch]
            case '#' : out += "#(2827)"; break; case '<' : out += "#(2927)"; break; // hard sign
            case '{' : case '[' : out += "#(2828)"; break; case '>' : out += "#(2928)"; break; // [y]
            case '}' : case ']' : out += "#(2829)"; break; case '@' : out += "#(2929)"; break; // soft sign
            case '%' : out += "#(2830)"; break; case '\\' : case '|' : out += "#(2930)"; break; // [eh]
            case '"' : out += "#(2831)"; break; case '^' : case '~' : out += "#(2931)"; break; // [yu]
            case 127u : case '_' : out += "#(2832)"; break; case ';' : out += "#(2932)"; break; // [ya]
            default : 
              out.append(in, i, 1);
              break;
          }
          break;
        case 4 : // greek letters
        case 7 :
          switch (in[i])
          {
            // non-equivalent letters
            case 'C' : out += "#gG"; break; case 'c' : out += "#gg"; break;
            case 'F' : out += "#gZ"; break; case 'f' : out += "#gz"; break;
            case 'G' : out += "#gY"; break; case 'g' : out += "#gy"; break;
            case 'J' : out += "#gK"; break; case 'j' : out += "#gk"; break;
            case 'K' : out += "#gL"; break; case 'k' : out += "#gl"; break;
            case 'L' : out += "#gM"; break; case 'l' : out += "#gm"; break;
            case 'M' : out += "#gN"; break; case 'm' : out += "#gn"; break;
            case 'N' : out += "#gC"; break; case 'n' : out += "#gc"; break;
            case 'Q' : out += "#gR"; break; case 'q' : out += "#gr"; break;
            case 'R' : out += "#gS"; break; case 'r' : out += "#gs"; break;
            case 'S' : out += "#gT"; break; case 's' : out += "#gt"; break;
            case 'T' : out += "#gU"; break; case 't' : out += "#gu"; break;
            case 'U' : out += "#gF"; break; case 'u' : out += "#gf"; break;
            case 'V' : out += "#gX"; break; case 'v' : out += "#gx"; break;
            case 'W' : out += "#gQ"; break; case 'w' : out += "#gq"; break;
            case 'X' : out += "#gW"; break; case 'x' : out += "#gw"; break;
            case 'Y' :                      case 'y' : out += "#(766)"; break;  
            case '{' : out += '['; break; case '}' : out += ']'; break;
            // equivalent letters
            case 'A' : case 'a' :
            case 'B' : case 'b' : 
            case 'D' : case 'd' :
            case 'E' : case 'e' :
            case 'H' : case 'h' :
            case 'I' : case 'i' :
            case 'O' : case 'o' :
            case 'P' : case 'p' :
              out += "#g";
            default : 
              out.append(in, i, 1);
              break;
          }
          break;
        case 3 : // simplex roman
          switch ((unsigned char)in[i])
          {
            // unsupported chars
            case '^' : case '~' : case '\\' :
              out += " "; 
              break;
            // 8th bit chars
            case 144u : out += "1"; break;
            case 154u : out += "#(218)"; break; // degree circle
            case 163u : out += "#(272)"; break; // pound sign
            case 167u : out += "#(2276)"; break; // paragraph
            case 169u : out += "#(274)"; break; // copyright sign
            case 174u : out += "#(273)"; break; // registered sign
            case 181u : out += "#gm"; break; // greek mu
            case 188u : out += "#(270)"; break; // 1/4
            case 189u : out += "#(261)"; break; // 1/2
            case 190u : out += "#(271)"; break; // 3/4
            case 215u : out += "#(846)"; break; // cross sign
            case 223u : out += "#fs#gb"; out += fonts[curr_fnt]; break; // beta script
            default : 
              out.append(in, i, 1);
              break;
          }
          break;
        default : // simply pass the char
          out.append(in, i, 1);
          break;
      }
      curr_fnt = next_fnt;
    }
  }  

retrn:
  if (debug) cout << "GDLGStream::TranslateFormatCodes(\"" << in << "\") = \"" << out << "\"" << endl;  
  return out.c_str();
}

void GDLGStream::mtex( const char *side, PLFLT disp, PLFLT pos, PLFLT just,
                       const char *text)
{
  plstream::mtex(side,disp,pos,just,TranslateFormatCodes(text));
}

void GDLGStream::ptex( PLFLT x, PLFLT y, PLFLT dx, PLFLT dy, PLFLT just,
                       const char *text)
{
  plptex(x,y,dx,dy,just,TranslateFormatCodes(text));
}
