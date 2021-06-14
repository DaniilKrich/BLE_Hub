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
    public class BleServicesController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public BleServicesController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: BleServices
        public async Task<IActionResult> Index()
        {
            return View(await _context.BleService.ToListAsync());
        }

        // GET: BleServices/Details/5
        public async Task<IActionResult> Details(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleService = await _context.BleService
                .FirstOrDefaultAsync(m => m.BleServiceID == id);
            if (bleService == null)
            {
                return NotFound();
            }

            return View(bleService);
        }

        // GET: BleServices/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: BleServices/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BleServiceID,SUUID,Name,Description")] BleService bleService)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bleService);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(bleService);
        }

        // GET: BleServices/Edit/5
        public async Task<IActionResult> Edit(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleService = await _context.BleService.FindAsync(id);
            if (bleService == null)
            {
                return NotFound();
            }
            return View(bleService);
        }

        // POST: BleServices/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(long id, [Bind("BleServiceID,SUUID,Name,Description")] BleService bleService)
        {
            if (id != bleService.BleServiceID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(bleService);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!BleServiceExists(bleService.BleServiceID))
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
            return View(bleService);
        }

        // GET: BleServices/Delete/5
        public async Task<IActionResult> Delete(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleService = await _context.BleService
                .FirstOrDefaultAsync(m => m.BleServiceID == id);
            if (bleService == null)
            {
                return NotFound();
            }

            return View(bleService);
        }

        // POST: BleServices/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(long id)
        {
            var bleService = await _context.BleService.FindAsync(id);
            _context.BleService.Remove(bleService);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool BleServiceExists(long id)
        {
            return _context.BleService.Any(e => e.BleServiceID == id);
        }
    }
}
