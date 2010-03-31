import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
#process.load('EventFilter.RPCRawToDigi.RPCFrontierCabling_cfi')

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'MC_31X_V1::All'
process.GlobalTag.globaltag = 'START3X_V18::All'


import EventFilter.RPCRawToDigi.rpcUnpacker_cfi

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/F4FE5D06-EB3B-DF11-8D16-0030487D0D3A.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/DEE7E9A9-FC3B-DF11-8BF8-001D09F23D1D.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/D01A79A5-FC3B-DF11-BC0F-001D09F23174.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/C0A5D466-EC3B-DF11-BDF4-000423D9A2AE.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/A8EAADF9-073C-DF11-B618-000423D94700.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/9CFF1A58-E83B-DF11-9AF2-0030487A322E.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/7E6AA362-083C-DF11-85EC-001D09F2516D.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/66CBD22E-003C-DF11-BD9E-001D09F2905B.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/5CA00C93-053C-DF11-924A-0030487A3C9A.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/32E33210-FE3B-DF11-A8D8-001D09F26C5C.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/1E2AA3C3-1A3C-DF11-AF37-0030487CD6D2.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/440/10CD830F-FA3B-DF11-997D-0030487C8E02.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/A2674AF9-173C-DF11-8166-000423D98DD4.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/86B38B5B-123C-DF11-8D59-0030487CD7C6.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/6688948C-0F3C-DF11-B0DB-000423D990CC.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/44947723-153C-DF11-915D-0030487C60AE.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/28C8B312-133C-DF11-9EF8-000423D6006E.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/1EDF60D5-0E3C-DF11-9245-0030487CD6DA.root',
'/store/data/Commissioning10/ZeroBias/RAW/v4/000/132/442/14349126-153C-DF11-A00B-0030487C608C.root'
    )
)


process.muonRPCDigis = EventFilter.RPCRawToDigi.rpcUnpacker_cfi.rpcunpacker.clone()

process.rpcRecHits = cms.EDProducer("RPCRecHitProducer",
    recAlgoConfig = cms.PSet(

    ),
    recAlgo = cms.string('RPCRecHitStandardAlgo'),
    rpcDigiLabel = cms.InputTag("muonRPCDigis"),
#   rpcDigiLabel = cms.InputTag("simMuonRPCDigis"),
    maskSource = cms.string('File'),
    maskvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCMaskVec.dat'),
    deadSource = cms.string('File'),
    deadvecfile = cms.FileInPath('RecoLocalMuon/RPCRecHit/data/RPCDeadVec.dat')
)


process.demo = cms.EDAnalyzer('RECHITANALIZER',
  eventfilename = cms.untracked.string('EVENTO.txt'),
  timefilename = cms.untracked.string('TIEMPO.txt')
)

process.FEVT = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *'),
    fileName = cms.untracked.string('/tmp/carrillo/RPCEvents.root')
)


process.RawToDigiRecHitDemo = cms.Sequence(process.muonRPCDigis*process.rpcRecHits*process.demo)
process.p = cms.Path(process.RawToDigiRecHitDemo)
process.outpath = cms.EndPath(process.FEVT)
