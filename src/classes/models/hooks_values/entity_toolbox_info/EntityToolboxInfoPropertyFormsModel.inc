<?php

/**
 * Class EntityToolboxInfoPropertyFormsModel
 */
class EntityToolboxInfoPropertyFormsModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'forms',
        'structure' => array(
          'edit' => array(
            'type'   => 'array',
            'method' => 'buildPropertyEditForm',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}