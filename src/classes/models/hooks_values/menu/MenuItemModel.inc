<?php

/**
 * Class MenuItemModel
 */
class MenuItemModel extends MenuRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(array(
      'structure' => array(
        'title'             => array(
          'type'    => 'string',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'title callback'    => array(
          'type'    => 'string',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'title arguments'   => array(
          'type'    => 'array',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'description'       => array(
          'type'    => 'string',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'page callback'     => array(
          'type'    => 'array',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'page arguments'    => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'delivery callback' => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'access callback'   => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'access argument'   => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'theme callback'    => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'theme arguments'   => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'file'              => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'file path'         => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'load arguments'    => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'weight'            => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'menu_name'         => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'expanded'          => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'context'           => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'tab_parent'        => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'tab_root'          => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'position'          => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'type'              => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
        'options'           => array(
          'type'    => '',
          'method'  => '',
          'default' => '',
          'model'   => '',
        ),
      )
    ), $args);
    parent::__construct($args);
  }
}