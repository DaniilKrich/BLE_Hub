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

        public StatusCodeResult AddBleHub(string name) //web-service
        {
            Ping ping = new Ping();
            var result = ping.Send(name);

            if (result.Status == IPStatus.Success)
            {
                var blehub = new BleHub(name);

                return new OkResult();
            }

            return new BadRequestResult();
        }

        // todo
        //GetNodes(blehub)
        public JsonResult GetNodes(string name)
        {
            //bleHub.IpAddress = null; //как его получить
            return new JsonResult("Nodes");
        }
        // GetServices(blehub,node)
        public JsonResult GetServices(int blehubID = 0, int nodeID = 0)
        {
            //var bles1 = new BleServices()
            //{

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



            //BleServices bleServices = GetServices();
            //return new JsonResult(bleServices);
            //return new JsonResult(bles1);
            return null;
        }
        // GetChannels(blehub,Service)
        public JsonResult GetChannels(BleHub bleHub, BleService bleService)
        {
            DigitalBleCharacteristic digitalChannel = new DigitalBleCharacteristic();
            AnalogBleCharacteristic analogChannel = new AnalogBleCharacteristic();
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
