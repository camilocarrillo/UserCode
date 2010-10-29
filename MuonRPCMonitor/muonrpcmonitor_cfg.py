import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Core.DQM_cfg")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/FA73D859-9DC7-DF11-BAD6-003048D37580.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/F8550624-A7C7-DF11-8A3C-003048F11C5C.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/EAF849CA-A0C7-DF11-9741-0030487CD718.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/E6403CDC-94C7-DF11-893B-001D09F25456.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/BE192522-8DC7-DF11-A068-001D09F23D1D.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/8AC27B4F-8AC7-DF11-A416-001D09F2546F.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/866C9E5A-98C7-DF11-8A4D-0030487CD700.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/8644C121-AEC7-DF11-B16A-001D09F23F2A.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/82AA719E-9CC7-DF11-BC7E-001D09F232B9.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/7E4E8E61-9FC7-DF11-BD3F-0030487CD6D8.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/6C9D50B5-97C7-DF11-B5E7-001D09F23A84.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/6617D46C-93C7-DF11-AFD3-001617DBD5AC.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/64F20E11-8BC7-DF11-81A0-001D09F2A49C.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/5A30385C-ABC7-DF11-98A2-000423D94E70.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/2A2A03BF-86C7-DF11-8981-000423D987E0.root',
'/store/data/Run2010B/MuMonitor/RECO/PromptReco-v2/000/146/511/0E6E56AD-90C7-DF11-A244-001D09F25217.root'
)
)

process.demo = cms.EDAnalyzer('MuonRPCMonitor',
#  tracks = cms.untracked.string('standAloneMuons'),
#  tracks = cms.untracked.string('standAloneSETMuons'), doesn't work
   tracks = cms.untracked.string('globalMuons'),
   rootFileName = cms.untracked.string('/tmp/carrillo/hscp.root'),
)


process.p = cms.Path(process.demo)
