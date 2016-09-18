<?php

/**
 * Class ThemeKeyBuilder
 */
class ThemeKeyBuilder extends HookKeyBuilder {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(
      array(
        'hook' => 'theme',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'module'      => $this->constructArgs['module']
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}