#!/opt/local/bin/bash

function pause(){
    read -p "$*"
}


#open -a /Applications/Utilities/Terminal.app 
open -a Terminal.app $1 --args $2
#pause 'Press any key to continue…'
