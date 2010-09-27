# Auto generated configuration file
# using: 
# Revision: 1.168.2.1 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: RelVal --step=DIGI,L1,DIGI2RAW,HLT --conditions=FrontierConditions_GlobalTag,STARTUP3X_V15::All --filein=rfio:/castor/cern.ch/user/g/gruen/cms/TTbarGenSim31X.root --fileout=RelVal_DigiL1RawHLT_8E29.root --number=100 --mc --no_exec --datatier GEN-SIM-DIGI-RAW-HLT --eventcontent=FEVTDEBUGHLT --customise=HLTrigger/Configuration/customL1THLT_Options.py --python_filename=RelVal_DigiL1RawHLT_8E29.py --processName=HLT
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT2')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.168.2.1 $'),
    annotation = cms.untracked.string('RelVal nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(400)
)
process.options = cms.untracked.PSet(

)
# Input source

process.load('list_cff')

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('/tmp/carrillo/RelVal_DigiL1RawHLT_8E29.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-HLT'),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'START3X_V26::All'

# Path and EndPath definitions
#process.digitisation_step = cms.Path(process.pdigi)
#process.L1simulation_step = cms.Path(process.SimL1Emulator)
#process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
#process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule = cms.Schedule(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])

# Automatic addition of the customisation function
def customise(process):
    if 'hltTrigReport' in process.__dict__:
        process.hltTrigReport.HLTriggerResults = cms.InputTag( 'TriggerResults','',process.name_() )

    if 'hltDQMHLTScalers' in process.__dict__:
        process.hltDQMHLTScalers.triggerResults = cms.InputTag( 'TriggerResults','',process.name_() )

    if 'hltDQML1SeedLogicScalers' in process.__dict__:
        process.hltDQML1SeedLogicScalers.processname = process.name_()

    process.options.wantSummary = cms.untracked.bool(True)
    process.MessageLogger.categories.append('TriggerSummaryProducerAOD')
    process.MessageLogger.categories.append('L1GtTrigReport')
    process.MessageLogger.categories.append('HLTrigReport')

    return(process)


# End of customisation function definition

process = customise(process)
