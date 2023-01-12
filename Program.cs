var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllersWithViews();

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

app.UseAuthorization();

app.UseEndpoints(endpoints => {
    endpoints.MapControllerRoute(
        name: "default",
        pattern: "{controller=Home}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Bookmarks",
        pattern: "{controller=Bookmarks}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Code",
        pattern: "{controller=Code}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Forget",
        pattern: "{controller=Forget}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Icon",
        pattern: "{controller=Icon}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Login",
        pattern: "{controller=Login}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Signup",
        pattern: "{controller=Signup}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Oauth",
        pattern: "{controller=Oauth}/{action=Index}");

    endpoints.MapControllerRoute(
        name: "Proform",
        pattern: "{controller=Proform}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Protour",
        pattern: "{controller=Protour}/{action=Index}");
    endpoints.MapControllerRoute(
        name: "Formor",
        pattern: "{controller=Formor}/{action=Index}");
});

/*app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");*/

app.Run();
