import FWCore.ParameterSet.Config as cms

process = cms.Process('SIMHITSHIFTER2')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('simhitshifter.SimHitShifter.simhitshifter_cfi')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')

process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_SHIFT.root'
   )
)

process.options = cms.untracked.PSet(
#    SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
                                        splitLevel = cms.untracked.int32(0),
                                        eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                        outputCommands = process.RAWSIMEventContent.outputCommands,
                                        fileName = cms.untracked.string('/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_DIGI_L1_DIGI2RAW_HLT_98_1_yUz.root'),
                                        dataset = cms.untracked.PSet(filterName = cms.untracked.string(''),
                                                                     dataTier = cms.untracked.string('GEN-SIM-SHIFT')
                                                                     ),
                                        )

# Additional output definition

# Other statements

process.GlobalTag.globaltag = 'START42_V11::All'

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition


##process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
##process.schedule = cms.Schedule(process.shifter_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
##process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)

## process.schedule = cms.Schedule(process.shifter_step) ##it produces the shifted simthits and works fine
## process.schedule = cms.Schedule(process.shifter_step,process.digitisation_step) ##but the digitization step fails do not find the mix 
process.schedule = cms.Schedule(process.digitisation_step)
                                
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWSIMoutput_step])



