<?php

/**
 * Class MenuItemBuilder
 */
class MenuItemBuilder extends MenuKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'MenuItemModel'
    ), $args);
    parent::__construct($args);
  }

  protected function buildTitle() {
  }

  protected function buildTitleCallback() {
  }

  protected function buildTitleArguments() {
  }

  protected function buildDescription() {
  }

  protected function buildPageCallback() {
  }

  protected function buildPageArguments() {
  }

  protected function buildDeliveryCallback() {
  }

  protected function buildAccessCallback() {
  }

  protected function buildAccessArgument() {
  }

  protected function buildThemeCallback() {
  }

  protected function buildThemeArguments() {
  }

  protected function buildFile() {
  }

  protected function buildFilePath() {
  }

  protected function buildLoadArguments() {
  }

  protected function buildWeight() {
  }

  protected function buildMenuName() {
  }

  protected function buildExpanded() {
  }

  protected function buildContext() {
  }

  protected function buildTabParent() {
  }

  protected function buildTabRoot() {
  }

  protected function buildPosition() {
  }

  protected function buildType() {
  }

  protected function buildOptions() {
  }
}