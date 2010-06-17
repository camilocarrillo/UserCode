import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/c/carrillo/efficiency/CMSSW_3_5_8/src/beta/SingleMuPt100_cfi_GEN_SIM_DIGI.root"
    )
)

process.demo = cms.EDAnalyzer('RECHITANALIZER',
  eventfilename = cms.untracked.string('EVENTO.txt'),
  timefilename = cms.untracked.string('TIEMPO.txt')
)

process.rpcRecHits = cms.EDProducer("RPCRecHitProducer",
    recAlgoConfig = cms.PSet(

    ),
    recAlgo = cms.string('RPCRecHitStandardAlgo'),
#   rpcDigiLabel = cms.InputTag("muonRPCDigis"),
    rpcDigiLabel = cms.InputTag("simMuonRPCDigis"),
    maskSource = cms.string('File'),
    maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
    deadSource = cms.string('File'),
    deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat')
)


process.p = cms.Path(process.rpcRecHits*process.demo)
