using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class FormcelController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}