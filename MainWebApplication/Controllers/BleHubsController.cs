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
            return View(await _context.BleHubs.ToListAsync());
        }

        public async Task<List<BleHub>> GetList()
        {
            return await _context.BleHubs.ToListAsync();
        }




        // GET: BleHubs/Details/5
        public async Task<IActionResult> Details(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHubs
                .FirstOrDefaultAsync(m => m.BleHubID == id);
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
        public async Task<IActionResult> Create([Bind("BleHubID,Name,Description")] BleHub bleHub)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bleHub);
                await _context.SaveChangesAsync();
               }
            return View(bleHub);
        }

        [HttpPost]
        public async Task<int> CreateFnc([Bind("Name")] BleHub bleHub)
        {
            if (ModelState.IsValid)
            {
                _context.Add(bleHub);
              return  await _context.SaveChangesAsync();
            }

            return -1;
        }





        // GET: BleHubs/Edit/5
        public async Task<IActionResult> Edit(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHubs.FindAsync(id);
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
        public async Task<IActionResult> Edit(long id, [Bind("BleHubID,Name,Description")] BleHub bleHub)
        {
            if (id != bleHub.BleHubID)
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
                    if (!BleHubExists(bleHub.BleHubID))
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
        public async Task<IActionResult> Delete(long? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var bleHub = await _context.BleHubs
                .FirstOrDefaultAsync(m => m.BleHubID == id);
            if (bleHub == null)
            {
                return NotFound();
            }

            return View(bleHub);
        }

        // POST: BleHubs/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(long id)
        {
            var bleHub = await _context.BleHubs.FindAsync(id);
            _context.BleHubs.Remove(bleHub);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool BleHubExists(long id)
        {
            return _context.BleHubs.Any(e => e.BleHubID == id);
        }
    }
}
