#! /bin/bash

# Inicializacion de la interfaz de usuario
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh

# Preparacion del ambiente de CMSSW 1.6.6
# cd ~/scratch0/CMSSW_1_6_6/src
eval `scramv1 runtime -sh`

# Preparacion del ambiente de CRAB
source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh


# cd ~/CMSSW_1_6_0/src/

# For getting a new proxy:
# source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh
# voms-proxy-init -voms cms -valid 200:00

