;
; Alain C., 23 April 2014: just moving this code
; from outside TEST_ARRAY_EQUAL to be common
;
; AC 2017-Feb
; hierarchy : Wide (default) > verbose > short
;
; AC 2017-03-09 : 
; - now testing if inputs are defines (ISA() != 0)
; - if type of "nb_pbs" is String, then used it as a message
;
pro BANNER_FOR_TESTSUITE, case_name, nb_pbs, help=help, test=test, $
                          short=short, verbose=verbose, wide=wide
;
mess1='First mandatory param: procedure name (string)'
mess2='Second mandatory param: errors number (>=0 integer) or string message'
mess3=' UNDEFINED !'
;
if KEYWORD_SET(help) then help=1 else help=0
;
if (N_PARAMS() NE 2) then begin
   MESSAGE, /continue, mess1
   MESSAGE, /continue, mess2
   help=1
endif else begin
   if ~ISA(case_name) then help=100
   if ~ISA(case_name,/string) then help=101
   if ISA(case_name,/string) then if N_ELEMENTS(case_name) GT 1 then help=102   
   ;;
   if ~ISA(nb_pbs) then help=200
   if ISA(nb_pbs) then if N_ELEMENTS(nb_pbs) GT 1 then help=216
   if ~ISA(nb_pbs,/number) AND ~ISA(nb_pbs,/string) then help=213
   if ISA(nb_pbs,/number) then if (FLOOR(nb_pbs) LT 0) then help=214
   if ISA(nb_pbs,/complex) then help=215
   ;;
   if help EQ 100 then MESSAGE, /continue, mess1+mess3
   if help EQ 101 then MESSAGE, /continue, 'first param must be a String input'
   if help EQ 102 then MESSAGE, /continue, 'first param must be a scalar-like String input'
   ;;
   if help EQ 200 then MESSAGE, /continue, mess2+mess3
   if help EQ 213 then MESSAGE, /continue, 'second param must be a positive integer or a string'
   if help EQ 214 then MESSAGE, /continue, 'Number of errrors must be >= 0 !'
   if help EQ 215 then MESSAGE, /continue, 'second param as a complex type not OK !'
   if help EQ 216 then MESSAGE, /continue, 'second param must be a scalar-like input'
endelse
;
if (help GT 0) then begin
   print, 'pro BANNER_FOR_TESTSUITE, case_name, nb_pbs, help=help, test=test, $'
   print, '                          short=short, verbose=verbose, wide=wide'
   print, ''
   print, 'both parameters are mandatory, second one can be a positive integer or a string'
   return
endif
;
; to avoid any residual troubles if inputs as one-element arrays
if SIZE(case_name,/n_dim) EQ 1 then case_name=case_name[0]
if SIZE(nb_pbs,/n_dim) EQ 1 then nb_pbs=nb_pbs[0]
;
prefixe='% '+STRUPCASE(case_name)+': '
indent="  "
;
if ISA(nb_pbs,/number) then begin
   message=' errors encountered during '+STRUPCASE(case_name)+' tests'
   if (nb_pbs GT 0) then begin
      message=STRCOMPRESS(STRING(nb_pbs),/remove_all)+message
   endif else begin
      message='NO'+message
   endelse
endif else begin
   ;; when we pass a String
   message=nb_pbs
endelse
message=indent+message+indent
;
; managing Keywords hierarchy. Default is "isWide"
;
isWide=1
isVerbose=0
isShort=0
;
if ~KEYWORD_SET(wide) then begin
    if KEYWORD_SET(verbose) then begin
        isWide=0
        isVerbose=1
        isShort=0
    endif else begin
        if KEYWORD_SET(short) then begin
            isWide=0
            isVerbose=0
            isShort=1
        endif
    endelse
endif
;
if (isShort) then begin
    print, prefixe, message
    return
endif
;
lenght=STRLEN(message)
sep ="="
line=""
vide=" "
blanc=""
for ii=0,lenght-1 do begin
   line=line+sep
   blanc=blanc+vide
endfor
;
print, prefixe, sep+line+sep
if (isWide) then print, prefixe, sep+blanc+sep
print, prefixe, sep+message+sep
if (isWide) then print, prefixe, sep+blanc+sep
print, prefixe, sep+line+sep
;
if KEYWORD_SET(test) then STOP
;
end
