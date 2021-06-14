using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using MainWebApplication.Data;
using MainWebApplication.Models;

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
