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
    public class BleHubsController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public BleHubsController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: BleHubs
        public async Task<IActionResult> Index()
        {
            return View(await _context.BleHub.ToListAsync());
        }

        // GET: BleHubs/Details/5
        public async Task<IActionResult> Details(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHub
                .FirstOrDefaultAsync(m => m.Name == id);
            if (bleHub == null)
            {
                return NotFound();
            }

            return View(bleHub);
        }

        // GET: BleHubs/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: BleHubs/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Name,Description")] BleHub bleHub)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bleHub);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(bleHub);
        }

        // GET: BleHubs/Edit/5
        public async Task<IActionResult> Edit(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHub.FindAsync(id);
            if (bleHub == null)
            {
                return NotFound();
            }
            return View(bleHub);
        }

        // POST: BleHubs/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(string id, [Bind("Name,Description")] BleHub bleHub)
        {
            if (id != bleHub.Name)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(bleHub);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!BleHubExists(bleHub.Name))
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
            return View(bleHub);
        }

        // GET: BleHubs/Delete/5
        public async Task<IActionResult> Delete(string id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHub
                .FirstOrDefaultAsync(m => m.Name == id);
            if (bleHub == null)
            {
                return NotFound();
            }

            return View(bleHub);
        }

        // POST: BleHubs/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(string id)
        {
            var bleHub = await _context.BleHub.FindAsync(id);
            _context.BleHub.Remove(bleHub);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool BleHubExists(string id)
        {
            return _context.BleHub.Any(e => e.Name == id);
        }
    }
}
