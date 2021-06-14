using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using MainWebApplication.Data;
using MainWebApplication.Models;

namespace MainWebApplication.Views
{
    public class DigitalValuesController : Controller
    {
        private readonly MainWebApplicationContext _context;

        public DigitalValuesController(MainWebApplicationContext context)
        {
            _context = context;
        }

        // GET: DigitalValues
        public async Task<IActionResult> Index()
        {
            var mainWebApplicationContext = _context.DigitalValue.Include(d => d.BleCharacteristic);
            return View(await mainWebApplicationContext.ToListAsync());
        }

        // GET: DigitalValues/Details/5
        public async Task<IActionResult> Details(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalValue = await _context.DigitalValue
                .Include(d => d.BleCharacteristic)
                .FirstOrDefaultAsync(m => m.Timestamp == id);
            if (digitalValue == null)
            {
                return NotFound();
            }

            return View(digitalValue);
        }

        // GET: DigitalValues/Create
        public IActionResult Create()
        {
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator");
            return View();
        }

        // POST: DigitalValues/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("BleCharacteristicID,Timestamp,Value")] DigitalValue digitalValue)
        {
            if (ModelState.IsValid)
            {
                _context.Add(digitalValue);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", digitalValue.BleCharacteristicID);
            return View(digitalValue);
        }

        // GET: DigitalValues/Edit/5
        public async Task<IActionResult> Edit(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalValue = await _context.DigitalValue.FindAsync(id);
            if (digitalValue == null)
            {
                return NotFound();
            }
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", digitalValue.BleCharacteristicID);
            return View(digitalValue);
        }

        // POST: DigitalValues/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to, for 
        // more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(DateTime id, [Bind("BleCharacteristicID,Timestamp,Value")] DigitalValue digitalValue)
        {
            if (id != digitalValue.Timestamp)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(digitalValue);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!DigitalValueExists(digitalValue.Timestamp))
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
            ViewData["BleCharacteristicID"] = new SelectList(_context.Set<BleCharacteristic>(), "BleCharacteristicID", "Discriminator", digitalValue.BleCharacteristicID);
            return View(digitalValue);
        }

        // GET: DigitalValues/Delete/5
        public async Task<IActionResult> Delete(DateTime? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var digitalValue = await _context.DigitalValue
                .Include(d => d.BleCharacteristic)
                .FirstOrDefaultAsync(m => m.Timestamp == id);
            if (digitalValue == null)
            {
                return NotFound();
            }

            return View(digitalValue);
        }

        // POST: DigitalValues/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(DateTime id)
        {
            var digitalValue = await _context.DigitalValue.FindAsync(id);
            _context.DigitalValue.Remove(digitalValue);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool DigitalValueExists(DateTime id)
        {
            return _context.DigitalValue.Any(e => e.Timestamp == id);
        }
    }
}
