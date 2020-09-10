using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class ProformController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public JsonResult pollingData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetPollingModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult settData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSettModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sItemData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSItemModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sTypeData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSTypeModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult sVeriData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSVeriModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult sLimitData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSlimitModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult sOperData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSoperModels(sRowsData, clientip));
        }

        [HttpPost]
        public JsonResult addData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetAddModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult deleteData([FromBody] dFormData dFormData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetDeleteModels(dFormData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] uFormsData uFormsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetInsertModels(uFormsData, clientip));
        }
    }
}