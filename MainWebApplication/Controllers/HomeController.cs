using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net;
using System.Net.NetworkInformation;
using System.Threading.Tasks;
using MainWebApplication.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;

namespace MainWebApplication.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            return View();
        }

        public JsonResult AddBleHub(string ipString) //web-service
        {

            if (IPAddress.TryParse(ipString, out IPAddress iPAddress))
            {
                Ping ping = new Ping();
                var result = ping.Send(iPAddress);

                if (result.Status == IPStatus.Success)
                {
                    var blehub = new BleHub(iPAddress);
                     
                    return new JsonResult("SUccess");

                    //return new JsonResult("SUccess");
                }

            };


            return new JsonResult("Fault");
        }

        // todo
        //GetNodes(blehub)
        public JsonResult GetNodes(BleHub bleHub)
        {
            bleHub.IpAddress = null; //как его получить
            return new JsonResult("Nodes");
        }
        // GetServices(blehub,node)
        public JsonResult GetServices(int blehubID = 0, int nodeID = 0)
        {
            //var bles1 = new BleServices() {

            //new BleService()
            //{
            //    GUID = "wrwrwrrerwr",
            //    Description = "test1",
            //    Name = "bles1",
            //    Channels = new List<Channel>()
            //    {
            //        new DigitalChannel(),
            //        new AnalogChannel(),
            //        new AnalogChannel()
            //    }
            //},
            // new BleService()
            //{
            //    GUID = "wrwrwrrerwr",
            //    Description = "test1",
            //    Name = "bles1",
            //    Channels = new List<Channel>()
            //    {
            //        new DigitalChannel(),
            //        new AnalogChannel(),
            //        new AnalogChannel()
            //    }
            //},

                //new BleService()
                //{
                //    GUID = "wrwrwrrerwr",
                //    Description = "test1",
                //    Name = "bles1",
                //    Channels = new List<Channel>()
                //    {
                //        new DigitalChannel(),
                //        new AnalogChannel(),
                //        new AnalogChannel()
                //    }
                //}
                //};



               // BleServices bleServices = GetServices();
            return new JsonResult(bleServices);
            //return new JsonResult(bles1);
        }
        // GetChannels(blehub,Service)
        public JsonResult GetChannels(BleHub bleHub, BleService bleService)
        {
            DigitalChannel digitalChannel = new DigitalChannel();
            AnalogChannel analogChannel = new AnalogChannel();
            return new JsonResult("");
        }
        // GetChannel(blehub,Service,channel)
        // GetChannelValue(blehub,Service,channel)




        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
