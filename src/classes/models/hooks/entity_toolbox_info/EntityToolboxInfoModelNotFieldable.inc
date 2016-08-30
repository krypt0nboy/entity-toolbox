<?php

/**
 * Class EntityToolboxInfoModelFieldable
 */
class EntityToolboxInfoModelNotFieldable extends EntityToolboxInfoModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'fieldable'        => array(
            'default' => FALSE,
          ),
          'has_revisions'    => array(
            'default' => FALSE,
          ),
          'has_translations' => array(
            'default' => FALSE,
          ),
          'exportable'       => array(
            'default' => TRUE,
          ),
          'bundle_entity'    => array(
            'type'   => 'string',
            'method' => 'buildBundleOf',
          ),
        )
      ), $args
    );
    parent::__construct($args);
  }
}