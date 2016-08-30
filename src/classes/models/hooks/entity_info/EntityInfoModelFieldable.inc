<?php

/**
 * Class EntityInfoModelFieldable
 */
class EntityInfoModelFieldable extends EntityInfoModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'fieldable'          => array(
            'default' => TRUE,
          ),
          'bundle keys'        => array(
            'type'   => 'array',
            'method' => 'buildBundleKeys',
          ),
          'inline entity form' => array(
            'type'   => 'array',
            'method' => 'buildInlineEntityForm',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}