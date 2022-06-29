#include "ui/about_tab.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

namespace ui {
AboutTab::AboutTab() {
    // Main table
    auto* table = new brls::BoxLayout(brls::BoxLayoutOrientation::HORIZONTAL);
    table->setSpacing(22);

    // Icon
    auto* iconTable = new brls::BoxLayout(brls::BoxLayoutOrientation::VERTICAL);
    auto* icon      = new brls::Image(BOREALIS_ASSET("img/quartz_256.png"));
    icon->setScaleType(brls::ImageScaleType::FIT);
    icon->setHeight(150);
    icon->setWidth(150);
    iconTable->addView(icon);
    iconTable->setWidth(200);
    table->addView(iconTable);

    // App details
    auto* detailsTable = new brls::BoxLayout(brls::BoxLayoutOrientation::VERTICAL);
    detailsTable->setWidth(500);
    detailsTable->setSpacing(20);

    // Name
    auto* name = new brls::Label(brls::LabelStyle::MEDIUM, "main/name"_i18n, true);

    name->setFontSize(40);
    detailsTable->addView(name);

    // Description
    detailsTable->addView(new brls::Label(brls::LabelStyle::REGULAR,
        "main/about/description"_i18n, true));

    // Github
    detailsTable->addView(
        new brls::Label(brls::LabelStyle::SMALL, "main/about/github"_i18n, true));

    // Made by
    detailsTable->addView(new brls::Label(brls::LabelStyle::SMALL,
        "main/about/made_by"_i18n, true));

    table->addView(detailsTable);
    this->addView(table);
}
} // namespace ui