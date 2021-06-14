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
    public class DigitalBleCharacteristicsController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public DigitalBleCharacteristicsController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: DigitalBleCharacteristics
        public async Task<IActionResult> Index()
        {
            var mainWebApplicationContext = _context.DigitalBleCharacteristic.Include(d => d.BleService);
            return View(await mainWebApplicationContext.ToListAsync());
        }

        // GET: DigitalBleCharacteristics/Details/5
        public async Task<IActionResult> Details(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalBleCharacteristic = await _context.DigitalBleCharacteristic
                .Include(d => d.BleService)
                .FirstOrDefaultAsync(m => m.BleCharacteristicID == id);
            if (digitalBleCharacteristic == null)
            {
                return NotFound();
            }

            return View(digitalBleCharacteristic);
        }

        // GET: DigitalBleCharacteristics/Create
        public IActionResult Create()
        {
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID");
            return View();
        }

        // POST: DigitalBleCharacteristics/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BleCharacteristicID,BleServiceID,CUUID,Name,Description,Direction")] DigitalBleCharacteristic digitalBleCharacteristic)
        {
            if (ModelState.IsValid)
            {
                _context.Add(digitalBleCharacteristic);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", digitalBleCharacteristic.BleServiceID);
            return View(digitalBleCharacteristic);
        }

        // GET: DigitalBleCharacteristics/Edit/5
        public async Task<IActionResult> Edit(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalBleCharacteristic = await _context.DigitalBleCharacteristic.FindAsync(id);
            if (digitalBleCharacteristic == null)
            {
                return NotFound();
            }
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", digitalBleCharacteristic.BleServiceID);
            return View(digitalBleCharacteristic);
        }

        // POST: DigitalBleCharacteristics/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(long id, [Bind("BleCharacteristicID,BleServiceID,CUUID,Name,Description,Direction")] DigitalBleCharacteristic digitalBleCharacteristic)
        {
            if (id != digitalBleCharacteristic.BleCharacteristicID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(digitalBleCharacteristic);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!DigitalBleCharacteristicExists(digitalBleCharacteristic.BleCharacteristicID))
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
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", digitalBleCharacteristic.BleServiceID);
            return View(digitalBleCharacteristic);
        }

        // GET: DigitalBleCharacteristics/Delete/5
        public async Task<IActionResult> Delete(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalBleCharacteristic = await _context.DigitalBleCharacteristic
                .Include(d => d.BleService)
                .FirstOrDefaultAsync(m => m.BleCharacteristicID == id);
            if (digitalBleCharacteristic == null)
            {
                return NotFound();
            }

            return View(digitalBleCharacteristic);
        }

        // POST: DigitalBleCharacteristics/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(long id)
        {
            var digitalBleCharacteristic = await _context.DigitalBleCharacteristic.FindAsync(id);
            _context.DigitalBleCharacteristic.Remove(digitalBleCharacteristic);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool DigitalBleCharacteristicExists(long id)
        {
            return _context.DigitalBleCharacteristic.Any(e => e.BleCharacteristicID == id);
        }
    }
}
