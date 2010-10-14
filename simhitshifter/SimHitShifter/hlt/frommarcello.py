# Auto generated configuration file
# using: 
# Revision: 1.168.2.1 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/PYTHIA6_Exotica_HSCP_stau200_cfg.py -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT:GRun --conditions 
# START3X_V26::All --eventcontent RAWSIM --mc --datatier GEN-SIM-RAW --processName=HLT --number=10 --no_exec --customise SimG4Core/CustomPhysics/Exotica_HSCP_SIM_cfi.py
import FWCore.ParameterSet.Config as cms

process = cms.Process('HSCP')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.mixSimHits.input = cms.VInputTag(cms.InputTag("g4SimHits","BSCHits"),
                                         cms.InputTag("g4SimHits","FP420SI"),
                                         cms.InputTag("theshifter","MuonCSCHits"),
                                         cms.InputTag("theshifter","MuonDTHits"),
                                         cms.InputTag("theshifter","MuonRPCHits"),
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

        
process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedEarly10TeVCollision_cff')
process.load('Configuration.StandardSequences.Sim_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.mergedtruth.simHitCollections.muon = cms.vstring ('theshifterMuonDTHits',
                                                          'theshifterMuonCSCHits',
                                                          'theshifterMuonRPCHits')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('simhitshifter.SimHitShifter.simhitshifter_cfi')
#from simhitshifter.SimHitShifter.simhitshifter_cfi import *
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('Configuration/GenProduction/python/PYTHIA6_Exotica_HSCP_stau200_cfg.py nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(3)
)
process.options = cms.untracked.PSet(

)
# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(
  SkipEvent = cms.untracked.vstring('ProductNotFound'),
  wantSummary = cms.untracked.bool(True)
)

# Output definition
camilo = cms.PSet(
        outputCommands = cms.untracked.vstring('keep *_theshifter_*_*','drop *_g4SimHits_Muon*Hits_*')
        )
process.RAWSIMEventContent.outputCommands.extend(camilo.outputCommands)
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('/tmp/carrillo/marcelloHSCP_stau200_GEN_SIM_SHIFT_DIGI_L1_DIGI2RAW_HLT_04.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
        ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.simMuonCSCDigis.InputCollection = 'theshifterMuonCSCHits'
process.simMuonRPCDigis.InputCollection = 'theshifterMuonRPCHits'
process.simMuonDTDigis.InputCollection = 'theshifterMuonDTHits'

process.GlobalTag.globaltag = 'START3X_V26::All'
process.generator = cms.EDFilter("Pythia6GeneratorFilter",
    pythiaPylistVerbosity = cms.untracked.int32(0),
    stopHadrons = cms.bool(False),
    filterEfficiency = cms.untracked.double(1.0),
    comEnergy = cms.double(7000.0),
    crossSection = cms.untracked.double(-1),
    maxEventsToPrint = cms.untracked.int32(0),
    gluinoHadrons = cms.bool(False),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
            'MSTJ(22)=2     ! Decay those unstable particles', 
            'PARJ(71)=10 .  ! for which ctau  10 mm', 
            'MSTP(2)=1      ! which order running alphaS', 
            'MSTP(33)=0     ! no K factors in hard cross sections', 
            'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
            'MSTP(52)=2     ! work with LHAPDF', 
            'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
            'MSTP(82)=4     ! Defines the multi-parton model', 
            'MSTU(21)=1     ! Check on possible errors during program execution', 
            'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
            'PARP(89)=1960. ! sqrts for which PARP82 is set', 
            'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
            'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
            'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
            'PARP(67)=2.5    ! amount of initial-state radiation', 
            'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
            'PARP(62)=1.25   ! ', 
            'PARP(64)=0.2    ! ', 
            'MSTP(91)=1      !', 
            'PARP(91)=2.1   ! kt distribution', 
            'PARP(93)=15.0  ! '),
        processParameters = cms.vstring('MSEL=39                  ! All SUSY processes ', 
            'IMSS(1) = 11             ! Spectrum from external SLHA file', 
            'IMSS(21) = 33            ! LUN number for SLHA File (must be 33)', 
            'IMSS(22) = 33            ! Read-in SLHA decay table ', 
            'MDCY(C1000015,1)=0       ! set the stau stable.'),
        parameterSets = cms.vstring('pythiaUESettings', 
            'processParameters', 
            'SLHAParameters'),
        SLHAParameters = cms.vstring('SLHAFILE = SimG4Core/CustomPhysics/data/isa-slha200GeV.out')
    ),
    hscpFlavor = cms.untracked.string('stau'),
    massPoint = cms.untracked.int32(200),
    slhaFile = cms.untracked.string('SimG4Core/CustomPhysics/data/isa-slha200GeV.out'),
    processFile = cms.untracked.string('SimG4Core/CustomPhysics/data/RhadronProcessList.txt'),
    particleFile = cms.untracked.string('SimG4Core/CustomPhysics/data/particles_stau_200_GeV.txt')
)
process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim*process.theshifter)

process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
#process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step)
#process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq


# Automatic addition of the customisation function

def customise(process):
    
	FLAVOR = process.generator.hscpFlavor.value()
	MASS_POINT = process.generator.massPoint.value()
	SLHA_FILE = process.generator.slhaFile.value()
	PROCESS_FILE = process.generator.processFile.value()
	PARTICLE_FILE = process.generator.particleFile.value()
	

	process.load("SimG4Core.CustomPhysics.CustomPhysics_cfi")
	process.customPhysicsSetup.particlesDef = PARTICLE_FILE

        process.g4SimHits.Watchers = cms.VPSet (
            cms.PSet(
            type = cms.string('RHStopTracer'),
            RHStopTracer = cms.PSet(
            verbose = cms.untracked.bool (False),
            traceParticle = cms.string ("(~|tau1).*"),
            stopRegularParticles = cms.untracked.bool (False)
            )        
            )
            )

	
	if FLAVOR=="gluino" or FLAVOR=="stop":
		process.customPhysicsSetup.processesDef = PROCESS_FILE
		process.g4SimHits.Physics = cms.PSet(
        process.customPhysicsSetup,
        DummyEMPhysics = cms.bool(True),
        G4BremsstrahlungThreshold = cms.double(0.5), ## cut in GeV    
        DefaultCutValue = cms.double(1.), ## cuts in cm,default 1cm    
        CutsPerRegion = cms.bool(True),
        Verbosity = cms.untracked.int32(0),
        type = cms.string('SimG4Core/Physics/CustomPhysics'),
        EMPhysics   = cms.untracked.bool(True),  ##G4 default true
        HadPhysics  = cms.untracked.bool(True),  ##G4 default true
        FlagBERT    = cms.untracked.bool(False),
        FlagCHIPS   = cms.untracked.bool(False),
        FlagFTF     = cms.untracked.bool(False),
        FlagGlauber = cms.untracked.bool(False),
        FlagHP      = cms.untracked.bool(False),
        GFlash = cms.PSet(
        GflashHistogram = cms.bool(False),
        GflashEMShowerModel = cms.bool(False),
        GflashHadronPhysics = cms.string('QGSP_BERT_EMV'),
        GflashHadronShowerModel = cms.bool(False)
        )
        )
		process.g4SimHits.G4Commands = cms.vstring('/tracking/verbose 1')

	elif FLAVOR =="stau":
		process.g4SimHits.Physics = cms.PSet(
        process.customPhysicsSetup,
        DummyEMPhysics = cms.bool(True),
        G4BremsstrahlungThreshold = cms.double(0.5), ## cut in GeV    
        DefaultCutValue = cms.double(1.), ## cuts in cm,default 1cm    
        CutsPerRegion = cms.bool(True),
        Verbosity = cms.untracked.int32(0),
        type = cms.string('SimG4Core/Physics/CustomPhysics'),
        )
		process.g4SimHits.G4Commands = cms.vstring('/tracking/verbose 1')
	
	else:
		print "Wrong flavor %s. Only accepted are gluino, stau, stop." % FLAVOR

	return process
	


# End of customisation function definition

process = customise(process)
