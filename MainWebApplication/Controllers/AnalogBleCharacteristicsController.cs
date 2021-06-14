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
    public class AnalogBleCharacteristicsController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public AnalogBleCharacteristicsController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: AnalogBleCharacteristics
        public async Task<IActionResult> Index()
        {
            var mainWebApplicationContext = _context.AnalogBleCharacteristic.Include(a => a.BleService);
            return View(await mainWebApplicationContext.ToListAsync());
        }

        // GET: AnalogBleCharacteristics/Details/5
        public async Task<IActionResult> Details(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogBleCharacteristic = await _context.AnalogBleCharacteristic
                .Include(a => a.BleService)
                .FirstOrDefaultAsync(m => m.BleCharacteristicID == id);
            if (analogBleCharacteristic == null)
            {
                return NotFound();
            }

            return View(analogBleCharacteristic);
        }

        // GET: AnalogBleCharacteristics/Create
        public IActionResult Create()
        {
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID");
            return View();
        }

        // POST: AnalogBleCharacteristics/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Unit,BleCharacteristicID,BleServiceID,CUUID,Name,Description,Direction")] AnalogBleCharacteristic analogBleCharacteristic)
        {
            if (ModelState.IsValid)
            {
                _context.Add(analogBleCharacteristic);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", analogBleCharacteristic.BleServiceID);
            return View(analogBleCharacteristic);
        }

        // GET: AnalogBleCharacteristics/Edit/5
        public async Task<IActionResult> Edit(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogBleCharacteristic = await _context.AnalogBleCharacteristic.FindAsync(id);
            if (analogBleCharacteristic == null)
            {
                return NotFound();
            }
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", analogBleCharacteristic.BleServiceID);
            return View(analogBleCharacteristic);
        }

        // POST: AnalogBleCharacteristics/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(long id, [Bind("Unit,BleCharacteristicID,BleServiceID,CUUID,Name,Description,Direction")] AnalogBleCharacteristic analogBleCharacteristic)
        {
            if (id != analogBleCharacteristic.BleCharacteristicID)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(analogBleCharacteristic);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!AnalogBleCharacteristicExists(analogBleCharacteristic.BleCharacteristicID))
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
            ViewData["BleServiceID"] = new SelectList(_context.BleService, "BleServiceID", "BleServiceID", analogBleCharacteristic.BleServiceID);
            return View(analogBleCharacteristic);
        }

        // GET: AnalogBleCharacteristics/Delete/5
        public async Task<IActionResult> Delete(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogBleCharacteristic = await _context.AnalogBleCharacteristic
                .Include(a => a.BleService)
                .FirstOrDefaultAsync(m => m.BleCharacteristicID == id);
            if (analogBleCharacteristic == null)
            {
                return NotFound();
            }

            return View(analogBleCharacteristic);
        }

        // POST: AnalogBleCharacteristics/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(long id)
        {
            var analogBleCharacteristic = await _context.AnalogBleCharacteristic.FindAsync(id);
            _context.AnalogBleCharacteristic.Remove(analogBleCharacteristic);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool AnalogBleCharacteristicExists(long id)
        {
            return _context.AnalogBleCharacteristic.Any(e => e.BleCharacteristicID == id);
        }
    }
}
