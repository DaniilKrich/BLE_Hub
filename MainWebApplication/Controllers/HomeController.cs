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

                if (result.Status==IPStatus.Success)
                    return new JsonResult("SUccess");

            };


            return new JsonResult("Fault");
        }

        // todo
        // GetServices(blehub)
        // GetChannels(blehub,Service)
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
