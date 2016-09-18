<?php

/**
 * Class ThemeRecursiveModel
 */
class ThemeRecursiveModel extends HookRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'theme',
      ),
      $args
    );
    parent::__construct($args);
  }
}