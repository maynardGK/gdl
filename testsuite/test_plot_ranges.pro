;
; under GNU GPL v3
; Alain Coulais, 20 june 2017
; 350 years of Paris Observatory today !
;
; This incredible bug was reported by René Gastaud !
; Intermitendly happen since 0.9.5 ... (see on u14.04)
;
; -----------------------------------------------
; 
; Modifications history :
;
; - 2019-11-06 : AC : should not be run when device is NULL
; (is it OK to extend for PS & SVG devices ?)
;
; -----------------------------------------------
;
pro TEST_PLOT_YRANGES, cumul_errors, negative=negative, $
                       test=test, verbose=verbose, debug=debug
;
nb_errors=0
;
message='pb with !Y.crange for case : '
sign='**POSITIVE**'
;
x=FINDGEN(10)
;
extended_ranges=[-0.001,0.,0.001]
expected=[[-2.,10],[0,10],[0,10]]
;
if KEYWORD_SET(negative) then begin   
   x=-x
   expected=[[-10.,0],[-10,0],[-10,2]]
   sign='**NEGATIVE**'
endif
;
for ii=0, N_ELEMENTS(extended_ranges)-1 do begin
   ;;
   plot, x+extended_ranges[ii]
   ;;
   if KEYWORD_SET(verbose) then begin
      print, 'Min :', MIN( x+extended_ranges[ii])
      print, 'Max :', MAX( x+extended_ranges[ii])
      print, 'expected !y.crange : ', expected[*,ii]
      print, 'effective !y.crange : ', !y.crange
   endif
   ;;
   if ~ARRAY_EQUAL(expected[*,ii], !y.crange) then begin
      ERRORS_ADD, nb_errors, STRCOMPRESS(message+sign+' : '+string(ii))
   endif
endfor
;
txt='TEST_PLOT_YRANGES '
BANNER_FOR_TESTSUITE, txt+sign, nb_errors, pref=txt, /short, verb=verbose
;
ERRORS_CUMUL, cumul_errors, nb_errors
;
if KEYWORD_SET(test) then STOP
;
end
;
; -------------------------------------------
;
pro TEST_PLOT_RANGES, help=help, verbose=verbose, no_exit=no_exit, test=test
;
if KEYWORD_SET(help) then begin
   print, 'pro TEST_PLOT_RANGES, help=help, verbose=verbose, $'
   print, '                      no_exit=no_exit, test=test'
   return
endif
;
; store the !p/!d env
save_p=!p
save_dname=!d.name
;
rname=ROUTINE_NAME()
;
if ~CHECK_IF_DEVICE_IS_OK(rname, /force) then begin
   if ~KEYWORD_SET(no_exit) then EXIT, status=77 else STOP
endif
;
TEST_PLOT_YRANGES, nb_errors
TEST_PLOT_YRANGES, nb_errors, /negative
;
; reset the initial !p/!d env.
!p=save_p
SET_PLOT, save_dname
;
; ----------------- final message ----------
;
BANNER_FOR_TESTSUITE, 'TEST_PLOT_RANGES', nb_errors
;
if (nb_errors GT 0) AND ~KEYWORD_SET(no_exit) then EXIT, status=1
;
if KEYWORD_SET(test) then STOP
;
end

