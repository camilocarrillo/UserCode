import FWCore.ParameterSet.Config as cms

process = cms.Process("RPCRHPROD")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")

process.load("Geometry.RPCGeometry.rpcGeometry_cfi")

process.load("RecoLocalMuon.RPCRecHit.rpcRecHits_cfi")

process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    debugFlag = cms.untracked.bool(True),
    debugVebosity = cms.untracked.uint32(10),
    fileNames = cms.untracked.vstring('file:/tmp/carrillo/testsingle10Rec400GeV.root')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/rechit300GeV.root')
)

process.p = cms.Path(process.rpcRecHits)
process.ep = cms.EndPath(process.out)


