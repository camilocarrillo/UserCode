import FWCore.ParameterSet.Config as cms

process = cms.Process('SIMHITSHIFTER')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('simhitshifter.SimHitShifter.simhitshifter_cfi')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')

process.mixSimHits.input = cms.VInputTag(cms.InputTag("g4SimHits","BSCHits"),
                                         cms.InputTag("g4SimHits","FP420SI"),
                                         cms.InputTag("g4SimHits","MuonCSCHits"),
                                         cms.InputTag("g4SimHits","MuonDTHits"),
                                         cms.InputTag("g4SimHits","MuonRPCHits"),
                                         cms.InputTag("g4SimHits","TotemHitsRP"),
                                         cms.InputTag("g4SimHits","TotemHitsT1"),
                                         cms.InputTag("g4SimHits","TotemHitsT2Gem"),
                                         cms.InputTag("g4SimHits","TrackerHitsPixelBarrelHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsPixelBarrelLowTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsPixelEndcapHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsPixelEndcapLowTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTECHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTECLowTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTIBHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTIBLowTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTIDHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTIDLowTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTOBHighTof"),
                                         cms.InputTag("g4SimHits","TrackerHitsTOBLowTof")
                                         )

process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')

process.load('Configuration.StandardSequences.CrossingFrameWriter_cff')

process.mergedtruth.simHitCollections.muon = cms.vstring ('g4SimHitsMuonDTHits',
                                                          'g4SimHitsMuonCSCHits',
                                                          'g4SimHitsMuonRPCHits')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
      'file:/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT_98_1_yUz.root'
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
                                        fileName = cms.untracked.string('/tmp/carrillo/HSCPstau_M_200_7TeV_pythia6_cff_py_GEN_SIM_SHIFT.root'),
                                        dataset = cms.untracked.PSet(filterName = cms.untracked.string(''),
                                                                     dataTier = cms.untracked.string('GEN-SIM-SHIFT')
                                                                     ),
                                        )

#camilo = cms.PSet(outputCommands = cms.untracked.vstring('keep *_theshifter_*_*','drop *_g4SimHits_Muon*Hits_*'))
#process.RAWSIMEventContent.outputCommands.extend(camilo.outputCommands)

# Additional output definition

# Other statements

process.simMuonCSCDigis.InputCollection = 'g4SimHitsMuonCSCHits'
process.simMuonRPCDigis.InputCollection = 'g4SimHitsMuonRPCHits'
process.simMuonDTDigis.InputCollection = 'g4SimHitsMuonDTHits'

process.GlobalTag.globaltag = 'START42_V11::All'


# Path and EndPath definitions
process.mix_step = cms.Path(process.pcfw)
process.shifter_step = cms.Path(process.theshifter)
process.simulation_step = cms.Path(process.psim*process.theshifter)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition


##process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
##process.schedule = cms.Schedule(process.shifter_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)

process.schedule = cms.Schedule(process.shifter_step,process.mix_step) ##it produces the shifted simthits and works fine
##process.schedule = cms.Schedule(process.mix_step) ##it produces the shifted simthits and works fine
## process.schedule = cms.Schedule(process.shifter_step,process.digitisation_step) ##but the digitization step fails do not find the mix 
## process.schedule = cms.Schedule(process.simulation_step,process.digitisation_step)
                                
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RAWSIMoutput_step])



