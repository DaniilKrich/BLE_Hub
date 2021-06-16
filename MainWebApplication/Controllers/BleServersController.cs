using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using MainWebApplication.Data;
using MainWebApplication.Models;
using System.Threading;

namespace MainWebApplication.Controllers
{
    public class BleServersController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public BleServersController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: BleServers
        public async Task<IActionResult> Index()
        {
            return View(await _context.BleServer.ToListAsync());
        }

        public JsonResult GetScanResults()
        {
            var env = new List<BleServer>
            {
                new BleServer()
                {
                    BleAdr = new byte[] {0xc4, 0x4f, 0x33, 0x7f, 0xcb, 0x9b } ,
                    Name = "Полевое устройство c4:4f:33:7f:cb:9b"
                },
                new BleServer()
                {
                    BleAdr = new byte[] {0x54, 0xef, 0xa7, 0xd1, 0x23, 0x19 } ,
                    Name = "Beacon"
                },
                new BleServer()
                {
                    BleAdr = new byte[] {0xd1, 0x61, 0x83, 0x9f, 0xa4, 0x20 } ,
                    Name = ""
                }
            };

           Thread.Sleep(3000);

            //return await _context.BleServer.ToListAsync();
            return  Json(env);
        }



        // GET: BleServers/Details/5
        public async Task<IActionResult> Details(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleServer = await _context.BleServer
                .FirstOrDefaultAsync(m => m.BleServerID == id);
            if (bleServer == null)
            {
                return NotFound();
            }

            return View(bleServer);
        }

        // GET: BleServers/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: BleServers/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BleServerID,Name")] BleServer bleServer)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bleServer);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(bleServer);
        }

        // GET: BleServers/Edit/5
        public async Task<IActionResult> Edit(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleServer = await _context.BleServer.FindAsync(id);
            if (bleServer == null)
            {
                return NotFound();
            }
            return View(bleServer);
        }

        // POST: BleServers/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(long id, [Bind("BleServerID,Name")] BleServer bleServer)
        {
            if (id != bleServer.BleServerID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(bleServer);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!BleServerExists(bleServer.BleServerID))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(bleServer);
        }

        // GET: BleServers/Delete/5
        public async Task<IActionResult> Delete(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleServer = await _context.BleServer
                .FirstOrDefaultAsync(m => m.BleServerID == id);
            if (bleServer == null)
            {
                return NotFound();
            }

            return View(bleServer);
        }

        // POST: BleServers/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(long id)
        {
            var bleServer = await _context.BleServer.FindAsync(id);
            _context.BleServer.Remove(bleServer);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool BleServerExists(long id)
        {
            return _context.BleServer.Any(e => e.BleServerID == id);
        }
    }
}
