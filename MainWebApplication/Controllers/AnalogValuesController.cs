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
    public class AnalogValuesController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public AnalogValuesController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: AnalogValues
        public async Task<IActionResult> Index()
        {
            var mainWebApplicationContext = _context.AnalogValue.Include(a => a.BleCharacteristic);
            return View(await mainWebApplicationContext.ToListAsync());
        }

        // GET: AnalogValues/Details/5
        public async Task<IActionResult> Details(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogValue = await _context.AnalogValue
                .Include(a => a.BleCharacteristic)
                .FirstOrDefaultAsync(m => m.Timestamp == id);
            if (analogValue == null)
            {
                return NotFound();
            }

            return View(analogValue);
        }

        // GET: AnalogValues/Create
        public IActionResult Create()
        {
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator");
            return View();
        }

        // POST: AnalogValues/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BleCharacteristicID,Timestamp,Value")] AnalogValue analogValue)
        {
            if (ModelState.IsValid)
            {
                _context.Add(analogValue);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", analogValue.BleCharacteristicID);
            return View(analogValue);
        }

        // GET: AnalogValues/Edit/5
        public async Task<IActionResult> Edit(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogValue = await _context.AnalogValue.FindAsync(id);
            if (analogValue == null)
            {
                return NotFound();
            }
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", analogValue.BleCharacteristicID);
            return View(analogValue);
        }

        // POST: AnalogValues/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(DateTime id, [Bind("BleCharacteristicID,Timestamp,Value")] AnalogValue analogValue)
        {
            if (id != analogValue.Timestamp)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(analogValue);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!AnalogValueExists(analogValue.Timestamp))
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
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", analogValue.BleCharacteristicID);
            return View(analogValue);
        }

        // GET: AnalogValues/Delete/5
        public async Task<IActionResult> Delete(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var analogValue = await _context.AnalogValue
                .Include(a => a.BleCharacteristic)
                .FirstOrDefaultAsync(m => m.Timestamp == id);
            if (analogValue == null)
            {
                return NotFound();
            }

            return View(analogValue);
        }

        // POST: AnalogValues/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(DateTime id)
        {
            var analogValue = await _context.AnalogValue.FindAsync(id);
            _context.AnalogValue.Remove(analogValue);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool AnalogValueExists(DateTime id)
        {
            return _context.AnalogValue.Any(e => e.Timestamp == id);
        }
    }
}
