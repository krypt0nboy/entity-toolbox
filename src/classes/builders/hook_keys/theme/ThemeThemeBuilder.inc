<?php

/**
 * Class ThemeThemeBuilder
 */
class ThemeThemeBuilder extends ThemeKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'model_class' => 'ThemeModel',
    ), $args);
    parent::__construct($args);
  }

  protected function buildVariables() {
  }

  protected function buildRenderElement() {
  }

  protected function buildFile() {
  }

  protected function buildPath() {
  }

  protected function builtTemplate() {
  }

  protected function buildFunction() {
  }

  protected function buildBaseHook() {
  }

  protected function buildPattern() {
  }

  protected function buildPreprocessFunctions() {
  }

  protected function buildOverridePreprocessFunctions() {
  }

  protected function buildType() {
  }

  protected function buildThemePath() {
  }
}