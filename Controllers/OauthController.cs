using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class OauthController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }
    }
}