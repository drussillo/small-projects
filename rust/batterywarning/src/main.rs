use gtk4 as gtk;
use gtk::prelude::*;
use gtk::{glib, Application, ApplicationWindow, Label, CssProvider};


fn run_app(app: &Application) {
    let css = "
        window { 
        color: #FF7777;
        background-color: #181818; 
        font-size: 38px; 
        font-family: \"UbuntuMono Nerd Font\"; 
        }";
    let provider = CssProvider::new();
    provider.load_from_data(css);

    let display = gtk::gdk::Display::default().expect("No display");
    gtk::style_context_add_provider_for_display(
        &display,
        &provider,
        gtk4::STYLE_PROVIDER_PRIORITY_APPLICATION,
    );

    let window = ApplicationWindow::builder()
        .application(app)
        .title("Battery Warning")
        .modal(true)
        .decorated(false)
        .default_width(450)
        .default_height(150)
        .build();

    let label = &Label::new(Some("Battery Low"));
    window.set_child(Some(label));

    // input
    let controller = gtk::EventControllerKey::new();
    controller.connect_key_pressed(move |_, key, key_code, modifier_type| {
        if key == gtk::gdk::Key::Escape {
            std::process::exit(0);
        }
        glib::Propagation::Proceed
    });
    window.add_controller(controller);

    // audio
    // TODO

    window.present();
}



fn main() -> glib::ExitCode {
    let application = Application::builder()
        .application_id("com.example.batterywarning")
        .build();

    application.connect_activate(run_app);

    application.run()
}
