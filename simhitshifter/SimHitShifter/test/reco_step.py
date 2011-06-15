# Auto generated configuration file
# using: 
# Revision: 1.303 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: ../Configuration/GenProduction/python/HSCPstop_M_130_7TeV_pythia6_cff.py -s RAW2DIGI,RECO --eventcontent RECOSIM --conditions START42_V11::All --datatier GEN-SIM-RECO --no_exec --filein=file:HSCPgluino_M_900_7TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.root --customise Configuration/GenProduction/Exotica_HSCP_EventContent_cfg.py -n 1000 import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# Input source
process.source = cms.Source("PoolSource",
     fileNames = cms.untracked.vstring('file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_DIGI_L1_DIGI2RAW.root')
#    fileNames = cms.untracked.vstring('file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_98_1_yUz.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.303 $'),
    annotation = cms.untracked.string('../Configuration/GenProduction/python/HSCPstop_M_130_7TeV_pythia6_cff.py nevts:1000'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    fileName = cms.untracked.string('/tmp/carrillo/HSCPstau_7TeV_pythia6_cff_py_RAW2DIGI_RECO.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RECO')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'START42_V11::All'

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.GenProduction.Exotica_HSCP_EventContent_cfg
# from Configuration.GenProduction.Exotica_HSCP_EventContent_cfg import customise 

#call to customisation function customise imported from Configuration.GenProduction.Exotica_HSCP_EventContent_cfg
# process = customise(process)

# End of customisation functions
