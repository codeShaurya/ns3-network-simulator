#include <ctime>
#include <sstream>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csmaca-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"

#include "csmaca-apps.h"

#define STARTAN 1
#define ENDAN 20

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("CsmacaSimulator");

Time endTime = Seconds(0);
Time startAnalysisTime = Seconds(0);
bool isAnalysisTime = false;
uint32_t totalPacketSize = 0;

void AppSenderRx(std::string path,
                 uint32_t numPkts,
                 Ptr<Packet> packet)
{
  if (isAnalysisTime)
  {
    totalPacketSize += packet->GetSize();
  }
  NS_LOG_INFO(path << "[numPkts]=" << numPkts << " [total]=" << totalPacketSize);
}

void AppSenderTx(std::string path,
                 Ptr<const Packet> packet)
{

  if (Simulator::Now() >= Seconds(STARTAN) && !isAnalysisTime)
  {
    isAnalysisTime = true;
    startAnalysisTime = Simulator::Now();
  }

  if (Simulator::Now() >= Seconds(STARTAN) + Seconds(ENDAN))
  {
    Time time = Simulator::Now() - startAnalysisTime;
    std::cout << (totalPacketSize * 8 / time.GetSeconds()) / 1000000 << std::endl;
    Simulator::Stop();
  }
}

void StartTxCallback(std::string path,
                     Ptr<const Packet> packet)
{
  NS_LOG_INFO("Send=" << packet);
}
int main(int argc, char *argv[])
{

  int nodeAmount = 2;
  int distance = 47;
  int rate = 114000000;
  uint64_t stream = 0;

  CommandLine cmd;
  cmd.AddValue("distance", "Distance apart to place nodes (in meters).", distance);
  cmd.AddValue("nodeAmount", "Number of nodes", nodeAmount);
  cmd.AddValue("rate", "transmission rate", rate);
  cmd.AddValue("stream", "random stream", stream);
  cmd.Parse(argc, argv);

  NS_LOG_INFO("Creating nodes.");
  NodeContainer nodes;
  nodes.Create(nodeAmount);
  InternetStackHelper internet;
  internet.Install(nodes);

  Config::SetDefault("ns3::CsmacaMac::Rate", UintegerValue(rate));

  NS_LOG_INFO("Create traffic source & sink.");
  Ptr<CsmacaNetDevice> netDevices[nodeAmount];
  NetDeviceContainer netDeviceContainer;
  for (int i = 0; i < nodeAmount; i++)
  {
    Ptr<Node> node = NodeList::GetNode(i);
    netDevices[i] = CreateObject<CsmacaNetDevice>();
    netDeviceContainer.Add(netDevices[i]);
    node->AddDevice(netDevices[i]);
  }
  int64_t currentStream = stream;
  for (int i = 0; i < nodeAmount; i++)
  {
    Ptr<Node> node = NodeList::GetNode(i);
    Ptr<CsmacaNetDevice> device = netDevices[i];
    Ptr<CsmacaPhy> phy = device->GetPhy();
    phy->SetMobility(node);
    phy->SetDevice(device);
    netDevices[i]->SetAddress(Mac48Address::Allocate());
    currentStream += netDevices[i]->GetMac()->AssignStreams(currentStream);
    currentStream += netDevices[i]->GetMac()->GetPhy()->AssignStreams(currentStream);
  }
  for (int i = 0; i < nodeAmount; i++)
  {
    Ptr<CsmacaChannel> channel = netDevices[i]->GetMac()->GetPhy()->GetChannel();
    for (int j = 0; j < nodeAmount; j++)
    {
      Ptr<CsmacaPhy> phy = netDevices[j]->GetMac()->GetPhy();
      channel->Add(phy);
    }
  }
  Ipv4AddressHelper ipAddrs;
  ipAddrs.SetBase("192.168.0.0", "255.255.255.0");
  ipAddrs.Assign(netDeviceContainer);

  NS_LOG_INFO("Installing static mobility; distance " << distance << " .");
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
  for (int i = 0; i < nodeAmount; i++)
  {
    positionAlloc->Add(Vector(0.0, distance * i, 0.0));
  }

  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install(nodes);

  NS_LOG_INFO("Create traffic source & sink.");
  for (int i = 0; i < nodeAmount; i++)
  {
    Ptr<Node> node = NodeList::GetNode(i);
    Ptr<CsmacaSender> sender = CreateObject<CsmacaSender>();
    Ptr<CsmacaReceiver> receiver = CreateObject<CsmacaReceiver>();
    sender->SetStartTime(Seconds(0));
    receiver->SetStartTime(Seconds(0));
    node->AddApplication(sender);
    node->AddApplication(receiver);
  }

  std::string Sender0("/NodeList/0/ApplicationList/*/$CsmacaSender/");
  std::string Sender1("/NodeList/1/ApplicationList/*/$CsmacaSender/");
  std::string Sender2("/NodeList/2/ApplicationList/*/$CsmacaSender/");
  Config::Set(Sender0 + "PacketSize", UintegerValue(1500));
  Config::Set(Sender0 + "Destination", Ipv4AddressValue("192.168.0.2"));
  Config::Set(Sender0 + "Interval", StringValue("ns3::ConstantRandomVariable[Constant=0.0001]"));
  std::string Receiver1("/NodeList/1/ApplicationList/*/$CsmacaReceiver/");
  Config::Set(Receiver1 + "NumPackets", UintegerValue(10000));

  Config::Connect("/NodeList/*/ApplicationList/*/$CsmacaReceiver/Rx", MakeCallback(&AppSenderRx));
  Config::Connect("/NodeList/*/ApplicationList/*/$CsmacaSender/Tx", MakeCallback(&AppSenderTx));
  Config::Connect("/$ns3::CsmacaPhy/StartTx", MakeCallback(&StartTxCallback));

  NS_LOG_INFO("Run Simulation.");
  Simulator::Run();
  Simulator::Destroy();
}