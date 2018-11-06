  echo $env:WXNAME $env:GMNAME
      if ( $env:platform -Match "mingw64630x8664") 
      {
      $env:WXNAME=""
      $env:GMNAME=""
      cd c:\projects\gdl
      cmd /E:ON /K scripts\mingw-bldgdl
      }
      else
      {
      C:\msys64\usr\bin\bash.exe -lc "cd /c/projects/gdl &&. ./scripts/appveyor_gdl.msys"
      }
